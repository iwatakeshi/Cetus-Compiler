#include <cassert>
#include <typeinfo>
#include <string.h>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"

// Variadic write macro for legibility
#define ASM(...) fprintf(m_outputfile, __VA_ARGS__); fprintf(m_outputfile, "\n");

// Get offset in local scope. 
// REQUIRED: *p has Attribute *m_attrib and SymName *m_symname 
#define GET_OFFSET Attribute atb = p->m_attribute;                     \
                   SymScope *scp = atb.m_scope;                        \
                   SymName *syn = p->m_symname;                        \
                   Symbol *sym = m_st->lookup(scp, syn->spelling());   \
                   int offset = sym->get_offset();                     \
                   offset += stackOffset;

class Codegen : public Visitor
{
  private:
    FILE* m_outputfile;
    SymTab *m_st;

    // Basic size of a word (integers and booleans) in bytes
    static const int wordsize = 4;

    // Local variable access offset: skip ebx, esi, edi in frame
    static const int stackOffset = 4 * wordsize; 

    int label_count; // Access with new_label

    // Helpers
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

        if (num_args) 
        {   // Check for arguments
            int offset = 2 * wordsize;//stackOffset;   // Track required offset for arg

            while (num_args) 
            {   // Step through all args
                ASM("\tpushl %d(%%ebp)", offset);   // Add arg to stack in reverse order
                sStack += wordsize;   // Increment record of stack memory size used for args
                offset += wordsize; // Increment offset to get next arg
                num_args--;   // Got an arg: decrement args remaining
            }
        }

        if (size_locals) 
        {   // if local vars record stack space usage and allocate space for them.
            sStack += size_locals;
            ASM("\tsubl $%d, %%esp", size_locals);
        }

        return sStack;
    }

    void emit_epilogue(int sStack)
    {
        if (sStack) 
        {   // If stack space is used for locals (args + temps) move esp to ignore
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
    
   // Gets address of m_lhs and value of m_expr, then updates address with value.
   void visitAssignment(Assignment* p)
    {   /* This works for Variable & DerefPointer. Strings are a work in progress.
            Probably wise to branch by basetype. Or just omit strings entirely! :-D */

        p->visit_children(this);        // stack has VALUE(m_expr) then ADDR(m_lhs)

        ASM("\tpopl %%ebx");            // m_expr value in ebx
        ASM("\tpopl %%eax");            // m_lhs addr in ebx

        if(p->m_lhs->m_attribute.m_basetype == bt_string)
        {           
            ASM("\tmovb %%ex, (%%eax)");   // put byte value into address. var updated!
        }
        else // m_lhs is not a string
        {
    		ASM("\tmovl %%ebx, (%%eax)");   // put value into address. var updated!
        }
    }

    //TODO
    void visitCall(Call* p)
    {
		p->m_lhs->accept(this); //Puts lhs on stack 
		ASM("\tpushl %%ecx");
		ASM("\tpushl %%edx");
		//push arguments in reverse order
		int argspace = p->m_expr_list->size() * wordsize;
		for(auto it = (p->m_expr_list->rbegin()); it != p->m_expr_list->rend(); it--)
		{
			(*it)->accept(this);
		}
		ASM("\tcall %s", p->m_symname->spelling());
		ASM("\taddl $%d, %%esp", argspace); //clear args
		ASM("\tpopl %%edx");
		ASM("\tpopl %%ecx");
    	
		ASM("\tpopl %%ebx"); 
		ASM("\tmovl %%eax, (%%ebx)"); //puts return value into lhs

	}

    void visitReturn(Return* p)
    {
      p->visit_children(this);   // value of m_expr to stack
      ASM("\tpopl %%eax");       // return value to eax
    }

    // Control flow
    void visitIfNoElse(IfNoElse* p)
    {
        int label = new_label();
        p->m_expr->accept(this);              // Put condition expr result on stack

        ASM("# BEGIN IfNoElse %d", label);   // add control flow comment: BEGIN
        ASM("\tpopl %%eax");                 // Move condition expr result to eax
        ASM("\tcmp $0, %%eax");              // Test result against 0 (FALSE)
        ASM("\tje IfNoElseFalse%d", label);  // Conditional jump if equal (FALSE) to label
        ASM("IfNoElseTrue%d:", label);       // Print label for TRUE for clarity (superfluous)

        p->m_nested_block->accept(this);      // Handle conditional code block

        ASM("IfNoElseFalse%d:", label);      // Print label for FALSE
        ASM("# END IfNoElse %d", label);     // add control flow comment: END
    }

    void visitIfWithElse(IfWithElse* p)
    {
        int label = new_label();
        p->m_expr->accept(this);                // Put condition expr result on stack

        ASM("# BEGIN IfWithElse %d", label);   // add control flow comment: BEGIN
        ASM("\tpopl %%eax");                   // Move condition expr result to eax
        ASM("\tcmp $0, %%eax");                // Test result against 0 (FALSE)
        ASM("\tje IfWithElseFalse%d", label);  // Conditional jump if equal (FALSE) to label
        ASM("IfWithElseTrue%d:", label);       // Print label for TRUE for clarity (superfluous)

        p->m_nested_block_1->accept(this);      // Handle conditional code block (TRUE)

        ASM("jmp IfWithElseEnd%d:", label);    // Unconditional jump to skip Else block
        ASM("IfWithElseFalse%d:", label);      // Print label for FALSE

        p->m_nested_block_2->accept(this);      // Handle conditional code block

        ASM("IfWithElseEnd%d:", label);        // Unconditional jump to skip Else block
        ASM("# END IfWithElse %d", label);     // add control flow comment: END
    }

    void visitWhileLoop(WhileLoop* p)
    {
        int label = new_label();

        ASM("# BEGIN WhileLoop %d", label);   // add control flow comment: BEGIN
        ASM("WhileLoop%d:", label);           // Print loop label

        p->m_nested_block->accept(this);       // Handle conditional code block

        p->m_expr->accept(this);               // Put condition expr result on stack
        ASM("\tpopl %%eax");                  // Move condition expr result to eax
        ASM("\tcmp $0, %%eax");               // Test result against 0 (FALSE)
        ASM("\tjne WhileLoop%d", label);      // Conditional jump if not equal (i.e., TRUE) to loop label
        ASM("# END WhileLoop %d", label);     // add control flow comment: END
    }

    void visitCodeBlock(CodeBlock *p)
    {
       p->visit_children(this);
    }

    // Variable declarations (no code generation needed)
    void visitDeclImpl(DeclImpl* p)     { /* Do nothing: Used for typechecking */ }
    void visitTInteger(TInteger* p)     { /* Do nothing: Used for typechecking */ }
    void visitTIntPtr(TIntPtr* p)       { /* Do nothing: Used for typechecking */ }
    void visitTBoolean(TBoolean* p)     { /* Do nothing: Used for typechecking */ }
    void visitTCharacter(TCharacter* p) { /* Do nothing: Used for typechecking */ }
    void visitTCharPtr(TCharPtr* p)     { /* Do nothing: Used for typechecking */ }
    void visitTString(TString* p)       { /* Do nothing: Used for typechecking */ }
 
    // Comparison operations
    // See: set* @ https://docs.oracle.com/cd/E19455-01/806-3773/instructionset-120/index.html

    void visitCompare(Compare* p)
    {
        p->visit_children(this);       // push values of m_expr_1 and m_expr_2 to stack
        ASM("popl %%ebx");             // m_expr_2 into ebx
        ASM("\tpopl %%eax");           // m_expr_1 into eax
        ASM("\tcmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("\tsete %%dl");            // conditional set dl on EQUAL
        ASM("\tmovzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("\tpushl %%eax");          // result to stack. Done.
    }

    void visitNoteq(Noteq* p)
    {
        p->visit_children(this);       // push values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");           // m_expr_2 into ebx
        ASM("\tpopl %%eax");           // m_expr_1 into eax
        ASM("\tcmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("\tsetne %%dl");           // conditional set dl on NOT EQUAL
        ASM("\tmovzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("\tpushl %%eax");          // result to stack. Done.
    }

    void visitGt(Gt* p)
    {
        p->visit_children(this);       // push values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");           // m_expr_2 into ebx
        ASM("\tpopl %%eax");           // m_expr_1 into eax
        ASM("\tcmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("\tsetg %%dl");            // conditional set dl on GREATER
        ASM("\tmovzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("\tpushl %%eax");          // result to stack. Done.
    }

    void visitGteq(Gteq* p)
    {
        p->visit_children(this);       // push values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");           // m_expr_2 into ebx
        ASM("\tpopl %%eax");           // m_expr_1 into eax
        ASM("\tcmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("\tsetge %%dl");           // conditional set dl on GREATER OR EQUAL
        ASM("\tmovzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("\tpushl %%eax");          // result to stack. Done.
    }

    void visitLt(Lt* p)
    {
        p->visit_children(this);       // push values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");           // m_expr_2 into ebx
        ASM("\tpopl %%eax");           // m_expr_1 into eax
        ASM("\tcmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("\tsetl %%dl");            // conditional set dl on LESS
        ASM("\tmovzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("\tpushl %%eax");          // result to stack. Done.
    }

    void visitLteq(Lteq* p)
    {
        p->visit_children(this);       // push values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");           // m_expr_2 into ebx
        ASM("\tpopl %%eax");           // m_expr_1 into eax
        ASM("\tcmpl %%eax, %%ebx");    // non-destructive sub: set flags
        ASM("\tsetle %%dl");           // conditional set dl on LESS OR EQUAL
        ASM("\tmovzbl %%dl, %%eax");   // move + extend bit in dl to eax
        ASM("\tpushl %%eax");          // result to stack. Done.
    }

    // Arithmetic and logic operations
    void visitAnd(And* p)
    {
        p->visit_children(this);      // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");          // m_expr_2 into ebx
        ASM("\tpopl %%eax");          // m_expr_1 into eax
        ASM("\tandl %%ebx, %%eax");   // logical AND. Result in eax
        ASM("\tpushl %%eax");         // result to stack. Done.
    }

    void visitOr(Or* p)
    {
        p->visit_children(this);     // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");         // m_expr_2 into ebx
        ASM("\tpopl %%ebx");         // m_expr_1 into eax
        ASM("\torl %%ebx, %%eax");   // logical OR. Result in eax
        ASM("\tpushl %%eax");        // result to stack. Done.
    }

    void visitMinus(Minus* p)
    {
        p->visit_children(this);      // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");          // m_expr_2 into ebx
        ASM("\tpopl %%ebx");          // m_expr_1 into eax
        ASM("\tsubl %%ebx, %%eax");   // subtract ebx from eax. Result in eax
        ASM("\tpushl %%eax");         // result to stack. Done.
    }

    void visitPlus(Plus* p)
    {
        p->visit_children(this);      // pushes values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");          // m_expr_2 into ebx
        ASM("\tpopl %%ebx");          // m_expr_1 into eax
        ASM("\taddl %%ebx, %%eax");   // add ebx to eax. Result in eax
        ASM("\tpushl %%eax");         // result to stack. Done.
    }

    void visitTimes(Times* p)
    {
        p->visit_children(this);   // push values of m_expr_1 and m_expr_2 to stack
        ASM("\tpopl %%ebx");       // m_expr_2 into ebx
        ASM("\tpopl %%ebx");       // m_expr_1 into eax
        ASM("\tcdq");              // sign extend into edx
        ASM("\timull %%ebx");      // multiply ebx*eax. Result in eax
        ASM("\tpushl %%eax");      // result to stack. Done.
    }

    void visitDiv(Div* p)
    {
        p->visit_children(this);   // push values of m_expr_1 (dividend) and m_expr_2 (divisor)
        ASM("\tpopl %%ebx");       // divisor into ebx
        ASM("\tpopl %%eax");       // dividend into eax
        ASM("\tcdq");              // sign extend into edx
        ASM("\tdivl %%ebx");       // divide. Result in eax
        ASM("\tpushl %%eax");      // result to stack. Done.
    }

    void visitNot(Not* p)
    {
        p->visit_children(this);     // Push result of m_expr to stack
        ASM("\tpopl %%eax");         // Pop result off stack
        ASM("\tmovl $1, %%ebx");     // Put "1" into ebx to signify "TRUE"
        ASM("\txor %%ebx, %%eax");   // XOR to invert value of m_expr
        ASM("\tpushl %%eax");        // result to stack. Done.
    }

    void visitUminus(Uminus* p)
    {
        p->visit_children(this);   // Push result of m_expr to stack
        ASM("\tpopl %%eax");       // Pop result to eax
        ASM("\tneg %%eax");        // Negate contents of eax. Thanks, IA-32!
        ASM("\tpushl %%eax");      // result to stack. Done.
    }

    // Variable and constant access
    void visitIdent(Ident* p)
    {
        GET_OFFSET                           // Calculate offset in scope
        ASM("\tpushl -%d(%%ebp)", offset);   // push value at offset for parent
    }

    void visitBoolLit(BoolLit* p)
    {
        p->visit_children(this);   // visit m_primitive, which pushes m_data
    }

    void visitCharLit(CharLit* p)
    {
        p->visit_children(this);   // visit m_primitive, which pushes m_data
    }

    void visitIntLit(IntLit* p)
    {
        p->visit_children(this);   // visit m_primitive, which pushes m_data
    }

    void visitNullLit(NullLit* p)
    {
      ASM("\tpushl $0");   // Push 0 to stack. Used for NULL ptrs.
    }

    // Pushes the char at index to stack
    void visitArrayAccess(ArrayAccess* p)
    {
        GET_OFFSET                 // Calculate offset in scope
        p->m_expr->accept(this);   // push index to stack

        ASM("\tmovl %d(%%ebp), %%esi", offset);   // move addr of array into esi
        ASM("\tpopl %%edx");                      // pop index to ebx

        ASM("\taddl %%edx, %%esi");   // Add index to address to get actual address
        ASM("\txorl %%eax, %%eax");   // Clear eax
        ASM("\tlodsb");               // Load byte at address in esi into al
        ASM("\tpushl %%eax");         // put byte (a char) onto stack, 4-aligned
    }

    // LHS return addresses

     // Pushes address of variable on stack
    void visitVariable(Variable* p)
    {   
        GET_OFFSET                          // Calculate offset in scope
        ASM("\tmovl $%d, %%ebx", offset);   // Put offset of var in ebx
		ASM("\tmovl %%ebp, %%eax");         // Put ebp in eax
		ASM("\tsubl %%ebx, %%eax");         // Get address of local (ebp-offset)
		ASM("\tpushl %%eax");               // Push address of local to stack
    }

   // Pushes address of referenced variable on stack
    void visitDerefVariable(DerefVariable* p)
    {
        GET_OFFSET                                 // Calculate offset in scope
        ASM("\tmovl -%d(%%ebp), %%eax", offset);   // Move ptr target offset to eax
        ASM("\tpushl %%eax");	                   // Push address of target variable to stack
    }

    // Pushes memory address of array element at index m_expr
    void visitArrayElement(ArrayElement* p)
    {
        /* Note: Char arrays are declared in data (see visitStringPrimitive)
            and memory addresses are stored on stack. sizeof(char) == 1B           */

        GET_OFFSET                                 // Calculate offset in scope
        ASM("\tmovl -%d(%%ebp), %%eax", offset);   // Move array address to eax

        p->m_expr->accept(this);      // Calculate index value
        ASM("\tpopl %%edx");          // Put index value in edx
        ASM("\taddl %%edx, %%eax");   // Add index to address to get element address
        ASM("\tpushl %%eax");         // Push result address for parent
    }

    // Special cases
    void visitSymName(SymName* p) { /* Do nothing: Used for typechecking */ }

    void visitPrimitive(Primitive* p)
    {   
        ASM("\tpushl $%d", p->m_data);   // Push the value to the stack
    }

    // Puts address of allocated string at offset on stack
    void visitStringAssignment(StringAssignment* p)
    {
        p->visit_children(this);        // esp has addr(string) then addr(m_lhs)
        ASM("\tpopl %%edx");            // Pop string addr to ebx
        ASM("\tpopl %%eax");            // Pop m_lhs addr to eax
        ASM("\tmovl %%edx, (%%eax)");   // Put string address on stack at local address
    }

    // Allocates data for a new string (char array) and pushes address thereof
    void visitStringPrimitive(StringPrimitive* p)
    {
        int label = new_label();

      	set_data_mode();
		ASM("String%d:", string);
		ASM("\t.asciz \"%s\"", p->m_string);   // Create null-terminated string in data
		set_text_mode();
		ASM("\tleal String%d, %%edi", label);        // Load address of first string element to stack
		ASM("\tpushl %%edi");                  // Push address to stack
    }

    // Returns by arg: strlen(m_expr) or abs(m_expr)
    void visitAbsoluteValue(AbsoluteValue* p)
    {
        int label = new_label();

        p->visit_children(this);  // m_expr is either offset of string or an int

        if(p->m_expr->m_attribute.m_basetype == bt_string)
        {   // m_expr is a string. Address of first char is on stack.
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
        {   // m_expr not a string. Value of m_expr is on stack
            ASM("\tpopl %%eax\n");           // Value to eax
            ASM("\ttest %%eax, %%eax");      // Bitwise AND, triggers Sign flag
            ASM("\tjns Unsigned%d", label);  // Jump if unsigned to skip negation
            ASM("\tneg %%eax");              // Negate on sign flag set
            ASM("Unsigned%d:", label);       // Now eax == |m_expr|
            ASM("\tpushl %%eax\n");          // Push result
        }
    }

    // Pointer

    // Pushes address of a Lhs to the stack
    void visitAddressOf(AddressOf* p)
    {
        p->visit_children(this);   // visits p->m_lhs, which puts address on stack  
    }

    // Pushes the value at the address contents of Lhs (a pointer)
    void visitDeref(Deref* p)
    {
        p->visit_children(this);   // visits p->m_expr, which puts ptr value on stack
        ASM("\tpopl %%eax");       // ptr value to eax
        ASM("\tpush (%%eax)");     // push value at location in eax, deref'ing ptr
    }
};


void dopass_codegen(Program_ptr ast, SymTab* st)
{
    Codegen* codegen = new Codegen(stdout, st);
    ast->accept(codegen);
    delete codegen;
}
