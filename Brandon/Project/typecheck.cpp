#include <iostream>
#include <cstdio>
#include <cstring>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "assert.h"

// WRITEME: The default attribute propagation rule
#define default_rule(X) \
    (X) -> m_attribute.m_scope = m_st -> get_scope();\
    (X) -> visit_children(this);

#include <typeinfo>

class Typecheck : public Visitor
{
  private:
    FILE* m_errorfile;
    SymTab* m_st;
    bool main_inserted;

    // The set of recognized errors
    enum errortype
    {
        no_main,//2
        nonvoid_main,
        dup_proc_name,
        dup_var_name,
        proc_undef,
        var_undef,
        narg_mismatch,
        arg_type_mismatch,
        ret_type_mismatch,
        call_type_mismatch,
        ifpred_err,
        whilepred_err,
        array_index_error,
        no_array_var,
        incompat_assign,
        expr_type_err,
        expr_abs_error,
        expr_pointer_arithmetic_err,
        expr_addressof_error,
        invalid_deref,
        who_knows//21
    };

    // Print the error to file and exit
    void t_error(errortype e, Attribute a)
    {
        fprintf(m_errorfile,"on line number %d, ", a.lineno);

        switch(e)
        {
            case no_main:
                fprintf(m_errorfile, "error: no main\n");
                exit(2);
            case nonvoid_main:
                fprintf(m_errorfile, "error: the Main procedure has arguments\n");
                exit(3);
            case dup_proc_name:
                fprintf(m_errorfile, "error: duplicate procedure names in same scope\n");
                exit(4);
            case dup_var_name:
                fprintf(m_errorfile, "error: duplicate variable names in same scope\n");
                exit(5);
            case proc_undef:
                fprintf(m_errorfile, "error: call to undefined procedure\n");
                exit(6);
            case var_undef:
                fprintf(m_errorfile, "error: undefined variable\n");
                exit(7);
            case narg_mismatch:
                fprintf(m_errorfile, "error: procedure call has different number of args than declartion\n");
                exit(8);
            case arg_type_mismatch:
                fprintf(m_errorfile, "error: argument type mismatch\n");
                exit(9);
            case ret_type_mismatch:
                fprintf(m_errorfile, "error: type mismatch in return statement\n");
                exit(10);
            case call_type_mismatch:
                fprintf(m_errorfile, "error: type mismatch in procedure call args\n");
                exit(11);
            case ifpred_err:
                fprintf(m_errorfile, "error: predicate of if statement is not boolean\n");
                exit(12);
            case whilepred_err:
                fprintf(m_errorfile, "error: predicate of while statement is not boolean\n");
                exit(13);
            case array_index_error:
                fprintf(m_errorfile, "error: array index not integer\n");
                exit(14);
            case no_array_var:
                fprintf(m_errorfile, "error: attempt to index non-array variable\n");
                exit(15);
            case incompat_assign:
                fprintf(m_errorfile, "error: type of expr and var do not match in assignment\n");
                exit(16);
            case expr_type_err:
                fprintf(m_errorfile, "error: incompatible types used in expression\n");
                exit(17);
            case expr_abs_error:
                fprintf(m_errorfile, "error: absolute value can only be applied to integers and strings\n");
                exit(17);
            case expr_pointer_arithmetic_err:
                fprintf(m_errorfile, "error: invalid pointer arithmetic\n");
                exit(18);
            case expr_addressof_error:
                fprintf(m_errorfile, "error: AddressOf can only be applied to integers, chars, and indexed strings\n");
                exit(19);
            case invalid_deref:
                fprintf(m_errorfile, "error: Deref can only be applied to integer pointers and char pointers\n");
                exit(20);
            default:
                fprintf(m_errorfile, "error: no good reason\n");
                exit(21);
        }
    }

    // Helpers
    // WRITEME: You might want write some hepler functions.

    // Type Checking
    // WRITEME: You need to implement type-checking for this project

    // Check that there is one and only one main
    void check_for_one_main(ProgramImpl* p)
    {
        if (! m_st -> lookup("Main")){// no Main in the program
            this -> t_error(no_main, p -> m_attribute);
        }

    }

    void add_proc_symbol(ProcImpl* p)
    {
        Symbol* s = new Symbol();
        s -> m_basetype = bt_procedure;

        char* name= strdup(p -> m_symname -> spelling());

        for (std::list<Decl_ptr>::iterator iter = p -> m_decl_list -> begin(); iter != p -> m_decl_list -> end(); ++iter){
            DeclImpl* decl = static_cast<DeclImpl*>(*iter);
            decl -> m_type -> accept( this );
            for (std::list<SymName_ptr>::iterator iter_d = decl -> m_symname_list -> begin(); iter_d != decl -> m_symname_list -> end(); ++iter_d){
                s -> m_arg_type.push_back(decl -> m_type -> m_attribute.m_basetype);
            }
        }

        p -> m_type -> accept(this);
        s -> m_return_type = p -> m_type -> m_attribute.m_basetype;

        if (strcmp(name, "Main") == 0){
            if (main_inserted)
                // duplicated Main in the source program
                this -> t_error(no_main, p -> m_attribute);
            else{
                m_st -> insert(name, s);
                main_inserted = true;
            }

            if (p -> m_decl_list -> size() != 0)
                // Main cannot have arguments
                this -> t_error(nonvoid_main, p -> m_attribute);

            return;
        }

        if (! m_st -> insert(name, s))
            this -> t_error(dup_proc_name,  p -> m_attribute);
    }

    // Add symbol table information for all the declarations following
    void add_decl_symbol(DeclImpl* p)
    {
        char* name;
        Symbol* s;
        for (std::list<SymName_ptr>::iterator iter = p -> m_symname_list -> begin(); iter != p -> m_symname_list -> end(); ++iter){
            name = strdup((*iter)->spelling());
            s = new Symbol();
            s -> m_basetype = p -> m_type -> m_attribute.m_basetype;
            if (s -> m_basetype == bt_string){
                s -> m_size = static_cast<TString*>(p -> m_type) -> m_primitive -> m_data;
            }

            if (! m_st -> insert(name, s))
                this -> t_error(dup_var_name, p -> m_attribute);
        }
    }

    // Check that the return statement of a procedure has the appropriate type
    void check_proc(ProcImpl *p)
    {
        Procedure_blockImpl* proc = static_cast<Procedure_blockImpl*> (p -> m_procedure_block);
        Basetype type_ret = proc -> m_return_stat -> m_attribute.m_basetype;
        Basetype type_ret_decl = p -> m_type -> m_attribute.m_basetype;
        if (type_ret != type_ret_decl)
            if (!(type_ret == bt_ptr && (type_ret_decl == bt_intptr || type_ret_decl == bt_charptr) ) )
                this -> t_error(ret_type_mismatch, p -> m_attribute);
    }

    // Check that the declared return type is not an array
    void check_return(Return *p)
    {
        if (p -> m_expr -> m_attribute.m_basetype == bt_string)
            this -> t_error(ret_type_mismatch, p -> m_attribute);
    }

    // Create a symbol for the procedure and check there is none already
    // existing
    void check_call(Call *p)
    {
        Symbol* s = m_st -> lookup(p -> m_symname -> spelling());
        if (! s || s -> m_basetype != bt_procedure)
            this -> t_error(proc_undef, p -> m_attribute);

        if (p -> m_expr_list -> size() != s -> m_arg_type.size())
             this -> t_error(narg_mismatch, p -> m_attribute);

        std::list<Expr_ptr>::iterator iter_expr = p -> m_expr_list -> begin();
        std::vector<Basetype>::iterator iter_param = s -> m_arg_type.begin();
        for (;iter_expr != p -> m_expr_list -> end() && iter_param != s -> m_arg_type.end();
          ++iter_expr,++iter_param){
            if ((*iter_expr) -> m_attribute.m_basetype != (*iter_param))
                this -> t_error(arg_type_mismatch, p -> m_attribute);
        }

       if (p -> m_lhs -> m_attribute.m_basetype != s -> m_return_type)
            this -> t_error(call_type_mismatch, p -> m_attribute);
    }

    // For checking that this expressions type is boolean used in if/else
    void check_pred_if(Expr* p)
    {
        if(p -> m_attribute.m_basetype != bt_boolean)
            this -> t_error(ifpred_err, p -> m_attribute);
    }

    // For checking that this expressions type is boolean used in while
    void check_pred_while(Expr* p)
    {
        if(p -> m_attribute.m_basetype != bt_boolean)
            this -> t_error(whilepred_err, p -> m_attribute);
    }

    // Characters can only assign characters to individual string (character array) elements.
    // The NULL pointer can be used as either a char pointer or an integer pointer.
    void check_assignment(Assignment* p)
    {
        Basetype typel = p -> m_lhs -> m_attribute.m_basetype;
        Basetype typer = p -> m_expr -> m_attribute.m_basetype;
        if ((typel == bt_charptr || typel == bt_intptr) && typer == bt_ptr)
            ;
        else if (typel != typer)
            this -> t_error(incompat_assign, p -> m_attribute);
    }

    void check_string_assignment(StringAssignment* p)
    {
        if(p -> m_lhs -> m_attribute.m_basetype != bt_string)
            this -> t_error(incompat_assign, p -> m_attribute);
    }

    void check_array_access(ArrayAccess* p)//rhs
    {
        Symbol* s = m_st -> lookup(p -> m_symname -> spelling());
        if (! s)
            this -> t_error(var_undef, p -> m_attribute);

        if(s -> m_basetype != bt_string)
            this -> t_error(no_array_var, p -> m_attribute);

        if (p -> m_expr -> m_attribute.m_basetype != bt_integer)
            this -> t_error(array_index_error, p -> m_attribute);
        //to do (s -> m_size)
    }

    void check_array_element(ArrayElement* p)//lhs
    {
        Symbol* s = m_st -> lookup(p -> m_symname -> spelling());
        if (! s)
            this -> t_error(var_undef, p -> m_attribute);

        if(s -> m_basetype != bt_string)
            this -> t_error(no_array_var, p -> m_attribute);

        if (p -> m_expr -> m_attribute.m_basetype != bt_integer)
            this -> t_error(array_index_error, p -> m_attribute);
    }

    // For checking boolean operations(and, or ...)
    void checkset_boolexpr(Expr* parent, Expr* child1, Expr* child2)
    {
        if (child1 -> m_attribute.m_basetype != bt_boolean || child2 -> m_attribute.m_basetype != bt_boolean)
            this -> t_error(expr_type_err, parent -> m_attribute);
        parent -> m_attribute.m_basetype = bt_boolean;
    }

    // For checking arithmetic expressions(plus, times, ...)
    void checkset_arithexpr(Expr* parent, Expr* child1, Expr* child2)
    {
        if (child1 -> m_attribute.m_basetype != bt_integer || child2 -> m_attribute.m_basetype != bt_integer)
            this -> t_error(expr_type_err, parent -> m_attribute);
        parent -> m_attribute.m_basetype = bt_integer;
    }

    // Called by plus and minus: in these cases we allow pointer arithmetics
    void checkset_arithexpr_or_pointer(Expr* parent, Expr* child1, Expr* child2)
    {
        //child1 -> m_attribute.m_basetype == bt_charptr || bt_intptr
        if (child2 -> m_attribute.m_basetype != bt_integer)
            this -> t_error(expr_pointer_arithmetic_err, parent -> m_attribute);
        parent -> m_attribute.m_basetype = child1 -> m_attribute.m_basetype;

    }

    // For checking relational(less than , greater than, ...)
    void checkset_relationalexpr(Expr* parent, Expr* child1, Expr* child2)
    {
       if (child1 -> m_attribute.m_basetype != bt_integer || child2 -> m_attribute.m_basetype != bt_integer)
            this -> t_error(expr_type_err, parent -> m_attribute);
        parent -> m_attribute.m_basetype = bt_boolean;
    }

    // For checking equality ops(equal, not equal)
    void checkset_equalityexpr(Expr* parent, Expr* child1, Expr* child2)
    {
        Basetype typel = child1 -> m_attribute.m_basetype;
        Basetype typer = child2 -> m_attribute.m_basetype;
        switch(typel){
            case bt_integer:
            case bt_boolean:
            case bt_char:
                if (typel != typer)
                    this -> t_error(expr_type_err,parent -> m_attribute);
                break;
            case bt_intptr:
            case bt_charptr:
                if (typel != typer && typer != bt_ptr)
                    this -> t_error(expr_type_err,parent -> m_attribute);
                break;
            case bt_ptr:
                if (typer != bt_integer && typer != bt_charptr)
                    this -> t_error(expr_type_err,parent -> m_attribute);
                break;
            default:
                this -> t_error(expr_type_err,parent -> m_attribute);
            }
        parent -> m_attribute.m_basetype = bt_boolean;
    }

    // For checking not
    void checkset_not(Expr* parent, Expr* child)
    {
        if (child -> m_attribute.m_basetype != bt_boolean)
            this -> t_error(expr_type_err,parent -> m_attribute);
        parent -> m_attribute.m_basetype = bt_boolean;
    }

    // For checking unary minus
    void checkset_uminus(Expr* parent, Expr* child)
    {
        if(child -> m_attribute.m_basetype != bt_integer)
            this -> t_error(expr_type_err, parent -> m_attribute);
        parent -> m_attribute.m_basetype = bt_integer;
    }

    void checkset_absolute_value(Expr* parent, Expr* child)
    {
        if (child -> m_attribute.m_basetype != bt_string && child -> m_attribute.m_basetype != bt_integer)
            this -> t_error(expr_abs_error,parent -> m_attribute);
        parent -> m_attribute.m_basetype = bt_integer;
    }

    void checkset_addressof(Expr* parent, Lhs* child)
    {
        if (child -> m_attribute.m_basetype == bt_char)
            parent -> m_attribute.m_basetype = bt_charptr;
        else if (child -> m_attribute.m_basetype == bt_integer)
            parent -> m_attribute.m_basetype = bt_intptr;
        else
            this -> t_error(expr_addressof_error,parent -> m_attribute);
    }

    void checkset_deref_expr(Deref* parent,Expr* child)
    {
        if(child -> m_attribute.m_basetype == bt_intptr)
            parent -> m_attribute.m_basetype = bt_integer;
        else if(child -> m_attribute.m_basetype == bt_charptr)
            parent -> m_attribute.m_basetype = bt_char;
        else
            this -> t_error(invalid_deref, parent -> m_attribute);
    }

    // Check that if the right-hand side is an lhs, such as in case of
    // addressof
    void checkset_deref_lhs(DerefVariable* p)
    {
        Symbol* s = m_st -> lookup(p -> m_symname -> spelling());
        if (! s)
            this -> t_error(var_undef, p -> m_attribute);

        if (s -> m_basetype == bt_intptr)
            p -> m_attribute.m_basetype = bt_integer;
        else if (s -> m_basetype == bt_charptr)
            p -> m_attribute.m_basetype = bt_char;
        else
            this -> t_error(invalid_deref, p -> m_attribute);
    }

    void checkset_variable(Variable* p)
    {
        Symbol* s = m_st -> lookup(p -> m_symname -> spelling());
        if (! s)
            this -> t_error(var_undef, p -> m_attribute);
        p -> m_attribute.m_basetype = s -> m_basetype;
    }


  public:

    Typecheck(FILE* errorfile, SymTab* st) {
        m_errorfile = errorfile;
        m_st = st;
        main_inserted = false;
    }

    void visitProgramImpl(ProgramImpl* p)
    {
        default_rule(p);
        check_for_one_main(p);
    }

    void visitProcImpl(ProcImpl* p)
    {
        // add the procedure symbol into the symbol table first in case that it iterative calls itself
        add_proc_symbol(p);//dup_proc_name
        m_st -> open_scope();
        default_rule(p);
        m_st -> close_scope();
        check_proc(p);//ret_type_mismatch
        // check_return(static_cast<Return*>(static_cast<Procedure_blockImpl*>(p -> m_procedure_block) -> m_return_stat));//ret_type_mismatch
    }

    void visitCall(Call* p)
    {
        default_rule(p);
        check_call(p);
    }

    void visitNested_blockImpl(Nested_blockImpl* p)
    {
        m_st -> open_scope();
        default_rule(p);
        m_st -> close_scope();
    }

    void visitProcedure_blockImpl(Procedure_blockImpl* p)
    {
        default_rule(p);
        p -> m_attribute.m_basetype = p -> m_return_stat -> m_attribute.m_basetype;
    }

    void visitDeclImpl(DeclImpl* p)
    {
        default_rule(p);
        add_decl_symbol(p);
    }

    void visitAssignment(Assignment* p)
    {
        default_rule(p);
        check_assignment(p);
    }

    void visitStringAssignment(StringAssignment *p)
    {
        default_rule(p);
        check_string_assignment(p);
    }

    void visitIdent(Ident* p)
    {
        default_rule(p);
        Symbol* s = m_st -> lookup(p -> m_symname -> spelling());
        if (! s)
            t_error(var_undef, p -> m_attribute);
        p -> m_attribute.m_basetype = s -> m_basetype;
     }

    void visitReturn(Return* p)
    {
        default_rule(p);
        check_return(p);
        p -> m_attribute.m_basetype = p -> m_expr -> m_attribute.m_basetype;
    }

    void visitIfNoElse(IfNoElse* p)
    {
        default_rule(p);
        check_pred_if(p -> m_expr);
    }

    void visitIfWithElse(IfWithElse* p)
    {
        default_rule(p);
        check_pred_if(p -> m_expr);
    }

    void visitWhileLoop(WhileLoop* p)
    {
        default_rule(p);
        check_pred_while(p ->  m_expr);
    }

    void visitCodeBlock(CodeBlock *p)
    {
        default_rule(p);
    }

    void visitTInteger(TInteger* p)
    {
        default_rule(p);
        p->m_attribute.m_basetype=bt_integer;
    }

    void visitTBoolean(TBoolean* p)
    {
        default_rule(p);
        p->m_attribute.m_basetype=bt_boolean;
    }

    void visitTCharacter(TCharacter* p)
    {
        default_rule(p);
        p->m_attribute.m_basetype=bt_char;
    }

    void visitTString(TString* p)
    {
        default_rule(p);
        p->m_attribute.m_basetype=bt_string;
    }

    void visitTCharPtr(TCharPtr* p)
    {
        default_rule(p);
        p->m_attribute.m_basetype=bt_charptr;
    }

    void visitTIntPtr(TIntPtr* p)
    {
        default_rule(p);
        p->m_attribute.m_basetype=bt_intptr;
    }

    void visitAnd(And* p)
    {
        default_rule(p);
        checkset_boolexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitDiv(Div* p)
    {
        default_rule(p);
        checkset_arithexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitCompare(Compare* p)
    {
        default_rule(p);
        checkset_equalityexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitGt(Gt* p)
    {
        default_rule(p);
        checkset_relationalexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitGteq(Gteq* p)
    {
        default_rule(p);
        checkset_relationalexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitLt(Lt* p)
    {
        default_rule(p);
        checkset_relationalexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitLteq(Lteq* p)
    {
        default_rule(p);
        checkset_relationalexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitMinus(Minus* p)
    {
        default_rule(p);
        Basetype typel = p -> m_expr_1 -> m_attribute.m_basetype;
        if (typel == bt_charptr)
            checkset_arithexpr_or_pointer(p, p -> m_expr_1, p-> m_expr_2);
        else
            checkset_arithexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitNoteq(Noteq* p)
    {
        default_rule(p);
        checkset_equalityexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitOr(Or* p)
    {
        default_rule(p);
        checkset_boolexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitPlus(Plus* p)
    {
        default_rule(p);
        Basetype typel = p -> m_expr_1 -> m_attribute.m_basetype;
        if (typel == bt_charptr)
            checkset_arithexpr_or_pointer(p, p -> m_expr_1, p-> m_expr_2);
        else
            checkset_arithexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitTimes(Times* p)
    {
        default_rule(p);
        checkset_arithexpr(p, p -> m_expr_1, p-> m_expr_2);
    }

    void visitNot(Not* p)
    {
        default_rule(p);
        checkset_not(p, p -> m_expr);
    }

    void visitUminus(Uminus* p)
    {
        default_rule(p);
        checkset_uminus(p, p -> m_expr);
    }

    void visitArrayAccess(ArrayAccess* p)
    {
        default_rule(p);
        check_array_access(p);
        p -> m_attribute.m_basetype = bt_char;
    }

    void visitIntLit(IntLit* p)
    {
        default_rule(p);
        p -> m_attribute.m_basetype = bt_integer;
    }

    void visitCharLit(CharLit* p)
    {
        default_rule(p);
        p -> m_attribute.m_basetype = bt_char;
    }

    void visitBoolLit(BoolLit* p)
    {
        default_rule(p);
        p -> m_attribute.m_basetype = bt_boolean;
    }

    void visitNullLit(NullLit* p)
    {
        default_rule(p);
        p -> m_attribute.m_basetype = bt_ptr;
    }

    void visitAbsoluteValue(AbsoluteValue* p)
    {
        default_rule(p);
        checkset_absolute_value(p, p -> m_expr);
    }

    void visitAddressOf(AddressOf* p)
    {
        default_rule(p);
        checkset_addressof(p, p -> m_lhs);
    }

    void visitVariable(Variable* p)
    {
        default_rule(p);
        checkset_variable(p);
    }

    void visitDeref(Deref* p)
    {
        default_rule(p);
        checkset_deref_expr(p, p -> m_expr);
    }

    void visitDerefVariable(DerefVariable* p)
    {
        default_rule(p);
        checkset_deref_lhs(p);
    }

    void visitArrayElement(ArrayElement* p)//lhs
    {
        default_rule(p);
        check_array_element(p);
        p -> m_attribute.m_basetype = bt_char;
    }

    // Special cases
    void visitPrimitive(Primitive* p) {}
    void visitSymName(SymName* p) {}
    void visitStringPrimitive(StringPrimitive* p) {}
};


void dopass_typecheck(Program_ptr ast, SymTab* st)
{
    Typecheck* typecheck = new Typecheck(stderr, st);

    ast->accept(typecheck);
    delete typecheck;
}
