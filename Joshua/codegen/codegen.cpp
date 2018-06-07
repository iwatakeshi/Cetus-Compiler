#include <cassert>
#include <typeinfo>
#include <string.h>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"

// Variadic write macro for legibility
#define ASM(...) fprintf(m_outputfile, __VA_ARGS__); fprintf(m_outputfile, "\n");

class Codegen : public Visitor
{
  private:
    FILE* m_outputfile;
    SymTab *m_st;

    // Basic size of a word (integers and booleans) in bytes
    static const int wordsize = 4;

    int label_count; // Access with new_label

    // Helpers
    // This is used to get new unique labels (cleverly names label1, label2, ...)
    int new_label()
    {
        return label_count++;
    }

    void set_text_mode()
    {
        fprintf(m_outputfile, ".text\n\n");
    }

    void set_data_mode()
    {
        fprintf(m_outputfile, ".data\n\n");
    }

    // PART 1:
    // 1) get arithmetic expressions on integers working:
    //  you wont really be able to run your code,
    //  but you can visually inspect it to see that the correct
    //  chains of opcodes are being generated.
    // 2) get procedure calls working:
    //  if you want to see at least a very simple program compile
    //  and link successfully against gcc-produced code, you
    //  need to get at least this far
    // 3) get boolean operation working
    //  before we can implement any of the conditional control flow
    //  stuff, we need to have booleans worked out.
    // 4) control flow:
    //  we need a way to have if-elses and while loops in our language.
    // 5) arrays: just like variables, but with an index

    // Hint: the symbol table has been augmented to track an offset
    //  with all of the symbols.  That offset can be used to figure
    //  out where in the activation record you should look for a particuar
    //  variable


    ///////////////////////////////////////////////////////////////////////////////
    //
    //  function_prologue
    //  function_epilogue
    //
    //  Together these two functions implement the callee-side of the calling
    //  convention.  A stack frame has the following layout:
    //
    //                         <- SP (before pre-call / after epilogue)
    //  high -----------------
    //       | actual arg 1  |
    //       |    ...        |
    //       | actual arg n  |
    //       -----------------
    //       |  Return Addr  |
    //       =================
    //       | temporary 1   | <- SP (when starting prologue)
    //       |    ...        |
    //       | temporary n   |
    //   low ----------------- <- SP (when done prologue)
    //
    //
    //              ||
    //              ||
    //             \  /
    //              \/
    //
    //
    //  The caller is responsible for placing the actual arguments
    //  and the return address on the stack. Actually, the return address
    //  is put automatically on the stack as part of the x86 call instruction.
    //
    //  On function entry, the callee
    //
    //  (1) allocates space for the callee's temporaries on the stack
    //
    //  (2) saves callee-saved registers (see below) - including the previous activation record pointer (%ebp)
    //
    //  (3) makes the activation record pointer (frmae pointer - %ebp) point to the start of the temporary region
    //
    //  (4) possibly copies the actual arguments into the temporary variables to allow easier access
    //
    //  On function exit, the callee:
    //
    //  (1) pops the callee's activation record (temporay area) off the stack
    //
    //  (2) restores the callee-saved registers, including the activation record of the caller (%ebp)
    //
    //  (3) jumps to the return address (using the x86 "ret" instruction, this automatically pops the
    //      return address off the stack
    //
    //////////////////////////////////////////////////////////////////////////////
    //
    // Since we are interfacing with code produced by GCC, we have to respect the
    // calling convention that GCC demands:
    //
    // Contract between caller and callee on x86:
    //    * after call instruction:
    //           o %eip points at first instruction of function
    //           o %esp+4 points at first argument
    //           o %esp points at return address
    //    * after ret instruction:
    //           o %eip contains return address
    //           o %esp points at arguments pushed by caller
    //           o called function may have trashed arguments
    //           o %eax contains return value (or trash if function is void)
    //           o %ecx, %edx may be trashed
    //           o %ebp, %ebx, %esi, %edi must contain contents from time of call
    //    * Terminology:
    //           o %eax, %ecx, %edx are "caller save" registers
    //           o %ebp, %ebx, %esi, %edi are "callee save" registers
    ////////////////////////////////////////////////////////////////////////////////


    // NOTE: Used https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax
    // Ugly & only used in visitProcImpl() - rewrite?
    int emit_prologue(SymName *name, unsigned int size_locals, unsigned int num_args)
    {
        int sStack = 0; // Track & return space used for args

        ASM(".globl %s", name->spelling());   // .globl $NAME
        ASM("%s:", name->spelling())          // $NAME:

        ASM("\tpushl %%ebp");         // Save ebp for ret
        ASM("\tmovl %%esp, %%ebp");   // New stack frame

        ASM("\tpushl %%ebx");   // Save "callee save" registers
        ASM("\tpushl %%esi");
        ASM("\tpushl %%edi");

        if (num_args) {   // Check for arguments
            int sOffset = wordsize * 2;   // Track required offset for arg

            while (num_args) {   // Step through all args
                ASM("\tpushl %d(%%ebp)",sOffset);   // Add arg to stack, reversing order as in notes above ** Edited

                sStack += wordsize;   // Increment record of stack memory size used for args
                sOffset += wordsize; // Increment offset to get next arg
                num_args--;   // Got an arg: decrement args remaining
            }
        }

        if (size_locals) {   // if local vars record stack space usage and allocate space for them.

            sStack += size_locals;
            ASM("\tsubl $%d, %%esp", size_locals);
        }

        return sStack;
    }

    void emit_epilogue(int sStack)
    {
        if (sStack) {   // If stack space is used for locals (args + temps) move esp to ignore
            ASM("\taddl $%d, %%esp", sStack);
        }

        ASM("\tpopl %%edi");          // Restore "callee save" registers
        ASM("\tpopl %%esi");
        ASM("\tpopl %%ebx");

        ASM("\tleave");   // Restores ebp & esp
        ASM("\tret");     // Returns to caller
    }

  public:

    Codegen(FILE* outputfile, SymTab* st)
    {
        m_outputfile = outputfile;
        m_st = st;
        label_count = 0;
    }

    void visitProgramImpl(ProgramImpl* p)
    {
        set_text_mode();
        p->visit_children(this);
    }

    void visitProcImpl(ProcImpl* p)
    {

        int sStack,
            localCount,
            argCount = 0;

        // Get local scope count
        localCount = m_st->scopesize(((Procedure_blockImpl *) p->m_procedure_block)->m_attribute.m_scope);

        // Get arg count
        for (auto it : *(p->m_decl_list)) {
            argCount += ((DeclImpl *)it)->m_symname_list->size(); // Cast to DeclImpl_ptr & accumulate
        }

        // Do prologue, recording allocated stack over min req'd
        sStack = emit_prologue(p->m_symname, localCount, argCount);

        // Descend
        p->visit_children(this);

        // Done! Do epilogue clearing allocated stack
        emit_epilogue(sStack);

    }

    void visitProcedure_blockImpl(Procedure_blockImpl* p)
    {
        p->visit_children(this);
    }

    void visitNested_blockImpl(Nested_blockImpl* p)
    {
        p->visit_children(this);
    }

    //TODO pretty sure this works now
    void visitAssignment(Assignment* p)
    {
        //navigate through the assignment class rather than visiting the children
        p->m_expr->accept(this);
        if(dynamic_cast<const AddressOf*>(p->m_expr) != 0){
           ASM("\tmovl %%ecx, %%eax");
        }
        //check the lhs
        p->m_lhs->accept(this);
        //If the lhs is an array element
        if(dynamic_cast<const ArrayElement*>(p->m_lhs) != 0){
           ASM("\tmovl %%eax, %%ecx");
           ASM("\tpopl %%eax");
        }
        if(dynamic_cast<const Variable*>(p->m_lhs) != 0 && p->m_lhs->m_attribute.m_basetype!=bt_string){
            ASM("\tmovl %%eax, %%ecx");
        }
        if(dynamic_cast<const DerefVariable*>(p->m_lhs) != 0){
           ASM("\tmovl %%eax, %%ecx");
        }
    }

    //TODO
    void visitCall(Call* p)
    {
		ASM("\tpushl %%ecx");
		ASM("\tpushl %%edx");
		//push arguments in reverse order
		for(auto it = (p->m_expr_list->rbegin()); it != p->m_expr_list->rend(); it--)
		{
			(*it)->accept(this);
		}
		ASM("\tcall %s", p->m_symname->spelling());
		
		ASM("\tpopl %%edx");
		ASM("\tpopl %%ecx");
    }

    void visitReturn(Return* p)
    {
      p->visit_children(this);
      ASM("\tpopl %%eax");
    }

    // Control flow
    void visitIfNoElse(IfNoElse* p)
    {
        int label = new_label();
        p->m_expr->accept(this);              // Put condition expr result on stack

        ASM("; BEGIN IfNoElse %d", label);   // add control flow comment: BEGIN
        ASM("\tpopl %%eax");                 // Move condition expr result to eax
        ASM("\tcmp $0, %%eax");              // Test result against 0 (FALSE)
        ASM("\tje IfNoElseFalse%d", label);  // Conditional jump if equal (FALSE) to label
        ASM("IfNoElseTrue%d:", label);       // Print label for TRUE for clarity (superfluous)

        p->m_nested_block->accept(this);      // Handle conditional code block

        ASM("IfNoElseFalse%d:", label);      // Print label for FALSE
        ASM("; END IfNoElse %d", label);     // add control flow comment: END
    }

    void visitIfWithElse(IfWithElse* p)
    {
        int label = new_label();
        p->m_expr->accept(this);                // Put condition expr result on stack

        ASM("; BEGIN IfWithElse %d", label);   // add control flow comment: BEGIN
        ASM("\tpopl %%eax");                   // Move condition expr result to eax
        ASM("\tcmp $0, %%eax");                // Test result against 0 (FALSE)
        ASM("\tje IfWithElseFalse%d", label);  // Conditional jump if equal (FALSE) to label
        ASM("IfWithElseTrue%d:", label);       // Print label for TRUE for clarity (superfluous)

        p->m_nested_block_1->accept(this);      // Handle conditional code block (TRUE)

        ASM("jmp IfWithElseEnd%d:", label);    // Unconditional jump to skip Else block
        ASM("IfWithElseFalse%d:", label);      // Print label for FALSE

        p->m_nested_block_2->accept(this);      // Handle conditional code block

        ASM("IfWithElseEnd%d:", label);        // Unconditional jump to skip Else block
        ASM("; END IfWithElse %d", label);     // add control flow comment: END
    }

    void visitWhileLoop(WhileLoop* p)
    {
        int label = new_label();

        ASM("; BEGIN WhileLoop %d", label);   // add control flow comment: BEGIN
        ASM("WhileLoop%d:", label);           // Print loop label

        p->m_nested_block->accept(this);       // Handle conditional code block

        p->m_expr->accept(this);               // Put condition expr result on stack
        ASM("\tpopl %%eax");                  // Move condition expr result to eax
        ASM("\tcmp $0, %%eax");               // Test result against 0 (FALSE)
        ASM("\tjne WhileLoop%d", label);      // Conditional jump if not equal (i.e., TRUE) to loop label
        ASM("; END WhileLoop %d", label);     // add control flow comment: END
    }

    void visitCodeBlock(CodeBlock *p)
    {
       p->visit_children(this);
    }

    // Variable declarations (no code generation needed)
    void visitDeclImpl(DeclImpl* p)
    {
        p->visit_children(this);
    }

    void visitTInteger(TInteger* p)
    {
        p->visit_children(this);
    }

    void visitTIntPtr(TIntPtr* p)
    {
        p->visit_children(this);
    }

    void visitTBoolean(TBoolean* p)
    {
        p->visit_children(this);
    }

    void visitTCharacter(TCharacter* p)
    {
        p->visit_children(this);

    }

    void visitTCharPtr(TCharPtr* p)
    {
        p->visit_children(this);
    }

    void visitTString(TString* p)
    {
        p->visit_children(this);
    }

    // Comparison operations
    // See: set* @ https://docs.oracle.com/cd/E19455-01/806-3773/instructionset-120/index.html

    void visitCompare(Compare* p)
    {
        p->visit_children(this);         // push values of m_expr_1 and m_expr_2 to stack
        ASM("popl %%ebx");            // m_expr_2 into ebx
        ASM("popl %%eax");            // m_expr_1 into eax
        ASM("cmpl %%eax, %%ebx");     // non-destructive sub: set flags
        ASM("sete %%dl");            // conditional set dl on EQUAL
        ASM("movzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("pushl %%eax");           // result to stack. Done.
    }

    void visitNoteq(Noteq* p)
    {
        p->visit_children(this);         // push values of m_expr_1 and m_expr_2 to stack
        ASM("popl %%ebx");            // m_expr_2 into ebx
        ASM("popl %%eax");            // m_expr_1 into eax
        ASM("cmpl %%eax, %%ebx");     // non-destructive sub: set flags
        ASM("setne %%dl");            // conditional set dl on NOT EQUAL
        ASM("movzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("pushl %%eax");           // result to stack. Done.
    }

    void visitGt(Gt* p)
    {
        p->visit_children(this);         // push values of m_expr_1 and m_expr_2 to stack
        ASM("popl %%ebx");           // m_expr_2 into ebx
        ASM("popl %%eax");           // m_expr_1 into eax
        ASM("cmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("setg %%dl");            // conditional set dl on GREATER
        ASM("movzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("pushl %%eax");          // result to stack. Done.
    }

    void visitGteq(Gteq* p)
    {
        p->visit_children(this);         // push values of m_expr_1 and m_expr_2 to stack
        ASM("popl %%ebx");           // m_expr_2 into ebx
        ASM("popl %%eax");           // m_expr_1 into eax
        ASM("cmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("setge %%dl");            // conditional set dl on GREATER OR EQUAL
        ASM("movzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("pushl %%eax");          // result to stack. Done.
    }

    void visitLt(Lt* p)
    {
        p->visit_children(this);         // push values of m_expr_1 and m_expr_2 to stack
        ASM("popl %%ebx");           // m_expr_2 into ebx
        ASM("popl %%eax");           // m_expr_1 into eax
        ASM("cmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("setl %%dl");            // conditional set dl on LESS
        ASM("movzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("pushl %%eax");          // result to stack. Done.
    }

    void visitLteq(Lteq* p)
    {
        p->visit_children(this);         // push values of m_expr_1 and m_expr_2 to stack
        ASM("popl %%ebx");           // m_expr_2 into ebx
        ASM("popl %%eax");           // m_expr_1 into eax
        ASM("cmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("setle %%dl");            // conditional set dl on LESS OR EQUAL
        ASM("movzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("pushl %%eax");          // result to stack. Done.
    }

    // Arithmetic and logic operations
    // Note: Children will resolve to stack
    void visitAnd(And* p)
    {
        p->visit_children(this);       // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");          // m_expr_2 into ebx
        ASM("\tpopl %%eax");          // m_expr_1 into eax
        ASM("\tandl %%ebx, %%eax");   // logical AND. Result in eax
        ASM("\tpushl eax");           // result to stack. Done.
    }

    void visitOr(Or* p)
    {
        p->visit_children(this);       // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");          // m_expr_2 into ebx
        ASM("\tpopl %%ebx");          // m_expr_1 into eax
        ASM("\torl %%ebx, %%eax");    // logical OR. Result in eax
        ASM("\tpushl eax");           // result to stack. Done.
    }

    void visitMinus(Minus* p)
    {
        p->visit_children(this);       // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");          // m_expr_2 into ebx
        ASM("\tpopl %%ebx");          // m_expr_1 into eax
        ASM("\tsubl %%ebx, %%eax");   // subtract ebx from eax. Result in eax
        ASM("\tpushl eax");           // result to stack. Done.
    }

    void visitPlus(Plus* p)
    {
        p->visit_children(this);       // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");          // m_expr_2 into ebx
        ASM("\tpopl %%ebx");          // m_expr_1 into eax
        ASM("\taddl %%ebx, %%eax");   // add ebx to eax. Result in eax
        ASM("\tpushl eax");           // result to stack. Done.
    }

    void visitTimes(Times* p)
    {
        p->visit_children(this);   // push values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");      // m_expr_2 into ebx
        ASM("\tpopl %%ebx");      // m_expr_1 into eax
        ASM("\tcdq");             // sign extend into edx
        ASM("\timull ebx");       // multiply ebx*eax. Result in eax
        ASM("\tpushl eax");       // result to stack. Done.
    }

    void visitDiv(Div* p)
    {
        p->visit_children(this);   // push values of m_expr_1 (dividend) and m_expr_2 (divisor)
        ASM("\tpopl %%ebx");      // divisor into ebx
        ASM("\tpopl %%eax");      // dividend into eax
        ASM("\tcdq");             // sign extend into edx
        ASM("\tdivl ebx");        // divide. Result in eax
        ASM("\tpushl eax");       // result to stack. Done.
    }

    void visitNot(Not* p)
    {
        p->visit_children(this);   // Push result of m_expr to stack
        ASM("popl %%eax");        // Pop result off stack
        ASM("movl $1, %%ebx");    // Put "1" into ebx to signify "TRUE"
        ASM("xor %%ebx, %%eax");  // XOR to invert value of m_expr
        ASM("pushl %%eax");       // result to stack. Done.
    }

    void visitUminus(Uminus* p)
    {
        p->visit_children(this);   // Push result of m_expr to stack
        ASM("\tpopl eax");        // Pop result to eax
        ASM("\tneg eax");         // Negate contents of eax. Thanks, IA-32!
        ASM("\tpushl eax");       // result to stack. Done.
    }

    // Variable and constant access
    void visitIdent(Ident* p)
    {
        p->visit_children(this);   // visit the symname
    }

    void visitBoolLit(BoolLit* p)
    {
      int value = p->m_primitive->m_data;
      ASM("\tpushl %d", value);
    }

    void visitCharLit(CharLit* p)
    {
      int value = p->m_primitive->m_data;
      ASM("\tpushl %d", value);
    }

    void visitIntLit(IntLit* p)
    {
      int value = p->m_primitive->m_data;
      ASM("\tpushl $%d", value);
    }

    void visitNullLit(NullLit* p)
    {
      ASM("\tpushl $0");   // Push 0 to stack. Used for NULL ptrs.
    }

    void visitArrayAccess(ArrayAccess* p)
    {
        //TODO: incomplete 
      p->m_expr->accept(this); //Array index
    }

    // LHS
    void visitVariable(Variable* p)
    {
        // Get variable offset
        int offset = -3 * wordsize; // skip ebx, esi, edi
        offset -= m_st->lookup(p->m_attribute.m_scope, p->m_symname->spelling())->get_offset();  // sub offset in scope

        ASM("\tpushl %d(%%ebp)", offset);   // Push value at offset to stack
    }

    void visitDerefVariable(DerefVariable* p)
    {
        // Get variable offset
        int offset = -3 * wordsize; // skip ebx, esi, edi
        offset -= m_st->lookup(p->m_attribute.m_scope, p->m_symname->spelling())->get_offset();  // sub offset in scope

        ASM("\tmovl %d(%%ebp), eax", offset);   // Move ptr target address to ebx
        ASM("\tpushl (%%eax)");   // Push value at memory address in eax to stack
    }

    void visitArrayElement(ArrayElement* p)
    {
    }

    // Special cases
    void visitSymName(SymName* p)
    {
    }

    void visitPrimitive(Primitive* p)
    {
      ASM("\tpushl $%d", p->m_data);   // Push value to stack
    }

    // Strings
    void visitStringAssignment(StringAssignment* p)
    {
		p->visit_children(this);
		//TODO Finish this!
    }

    void visitStringPrimitive(StringPrimitive* p)
    {
      	set_data_mode();
		int label = new_label();
		ASM("\t%d:", label);
		ASM("\t\t.asciz \"%s\"", p->m_string);
		set_text_mode();
		ASM("\tleal %d, %%edi", label);
		ASM("\tpushl %%edi");
    }

    void visitAbsoluteValue(AbsoluteValue* p)
    {
        p->visit_children(this);  // m_expr is either offset of string or an int

        if(p->m_expr->m_attribute.m_basetype == bt_string)
        {   // m_expr is a string. Address of first char is on stack. (tested)
            int label = new_label();
            ASM("\tpopl %%esi");            // Put address of first char into esi
            ASM("\txorl %%edi,%%edi");      // Clear edi
            ASM("LookChar%d:", label);                
            ASM("\tlodsb");                 // load byte at address in esi into al
            ASM("\tcmpb $0,%%al");          // compare byte (char) to null terminator
            ASM("\tjz FoundTerm%d", label); // if zero flag, then null term found
            ASM("\tincl %%edi");            // increment counter
            ASM("\tjmp LookChar%d", label); // 
            ASM("FoundTerm%d:", label);     
            ASM("\tpushl %%edi");           // put string length on stack
        }
        else
        {   // m_expr not a string. Value of expr is on stack
            ASM("\tpopl %%eax\n");
            ASM("\ttest %%eax, %%eax");  // bitwise AND, triggers Sign flag
            int label = new_label();
            ASM("\tjns label%d", label);  // Negate only if signed
            ASM("\tneg %%eax");
            ASM("label%d:", label);
            ASM("\tpushl %%eax\n");
        }
    }

    // Pointer
    void visitAddressOf(AddressOf* p)
    {
    }

    void visitDeref(Deref* p)
    {
    }
};


void dopass_codegen(Program_ptr ast, SymTab* st)
{
    Codegen* codegen = new Codegen(stdout, st);
    ast->accept(codegen);
    delete codegen;
}
