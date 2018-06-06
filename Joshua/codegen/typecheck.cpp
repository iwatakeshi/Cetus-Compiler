#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "assert.h"

// WRITEME: The default attribute propagation rule
#define default_rule(X) \
(X)->m_attribute.m_scope = m_st->get_scope(); \
(X)->visit_children(this); \

#include <typeinfo>

class Typecheck : public Visitor
{
  private:
    FILE* m_errorfile;
    SymTab* m_st;

    // The set of recognized errors
    enum errortype
    {
        no_main,
        nonvoid_main,
        dup_proc_name,
        dup_var_name,
        proc_undef,
        call_type_mismatch,
        narg_mismatch,
        expr_type_err,
        var_undef,
        ifpred_err,
        whilepred_err,
        incompat_assign,
        who_knows,
        ret_type_mismatch,
        array_index_error,
        no_array_var,
        arg_type_mismatch,
        expr_pointer_arithmetic_err,
        expr_abs_error,
        expr_addressof_error,
        invalid_deref
    };

  int mainCount = 0;

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

  void print_type(Basetype bt){
      switch(bt){
        case bt_ptr:
          printf(" ptr ");
          break;
        case bt_undef:
          printf(" undef ");
          break;
        case bt_intptr:
          printf(" intptr ");
          break;
        case bt_char:
          printf(" char ");
          break;
        case bt_string:
          printf(" string ");
          break;
        case bt_integer:
          printf(" integer ");
          break;
        case bt_boolean:
          printf(" boolean ");
          break;
        case bt_procedure:
          printf(" procedure ");
          break;
        case bt_charptr:
          printf(" charptr ");
          break;
        default:
          printf(" type not found ");
      }
    }

    // Type Checking
    // WRITEME: You need to implement type-checking for this project

    // Check that there is one and only one main
    void check_for_one_main(ProgramImpl* p)
    {
      Symbol *sym;
      sym = m_st->lookup("Main");
      if(sym == NULL){
	this->t_error(no_main, p->m_attribute);
      }
      if(sym->m_basetype != bt_procedure){
	this->t_error(no_main, p->m_attribute);
      }
      if(sym->m_arg_type.size() > 0){
	t_error(nonvoid_main, p->m_attribute);
      }
      if(mainCount > 1){
	this->t_error(no_main, p->m_attribute);
      }

    }

    // Create a symbol for the procedure and check there is none already
    // existing
    void add_proc_symbol(ProcImpl* p)
    {
      Symbol *sym = new Symbol();
      sym->m_basetype = bt_procedure;
      //sym->m_spelling = p->m_symname->spelling();
      sym->m_return_type = p->m_type->m_attribute.m_basetype;
      const char* Name = p->m_symname->spelling();
      char* procName = strdup(Name);
      bool alreadyExists = !(m_st->insert(procName, sym));
      if(alreadyExists){
	this->t_error(dup_proc_name, p->m_attribute);
      }

      //ADD ALL PARAMS TO SYMBOL TABLE
      std::list<Decl_ptr>::iterator i;
      for(i = p->m_decl_list->begin(); i != p->m_decl_list->end(); i++){
	Basetype paramType = static_cast<DeclImpl*>(*i)->m_type->m_attribute.m_basetype;
	sym->m_arg_type.push_back(paramType);
      }
    }

    // Add symbol table information for all the declarations following
    void add_decl_symbol(DeclImpl* p)
  {
      std::list<SymName_ptr>::iterator i;
      for(i = p->m_symname_list->begin(); i != p->m_symname_list->end(); i++){
	Symbol *sym = new Symbol();
	sym->m_basetype = p->m_type->m_attribute.m_basetype;
  Basetype b = p->m_type->m_attribute.m_basetype;
	const char* Name = (*i)->spelling();
	char* declName = strdup(Name);
	//printf(declName);
	//print_type(sym->m_basetype);
	bool alreadyExists = !(m_st->insert(declName, sym));
	if(alreadyExists){
	  this->t_error(dup_var_name, p->m_attribute);
	}
      }
  }


  const char* expr_to_id(Expr* e)
  {
    Ident *i = dynamic_cast<Ident*>(e);
    if(i) {
      //printf("expr_to_id: ");
      //printf(v->m_symname->spelling());
      return i->m_symname->spelling();
    }i
	
  }


    // Check that the return statement of a procedure has the appropriate type
    void check_proc(ProcImpl *p)
    {
      Basetype expected = p->m_type->m_attribute.m_basetype;
      Basetype actual = static_cast<Return *>(static_cast<Procedure_blockImpl *>  (p->m_procedure_block)->m_return_stat)->m_expr->m_attribute.m_basetype;

      if(actual == bt_undef){
	printf("actual = bt_undef");
	Expr* e = static_cast<Return *>(static_cast<Procedure_blockImpl *>
	(p->m_procedure_block)->m_return_stat)->m_expr;
	const char* name = expr_to_id(e);
	//printf("name = ");
	//printf(name);
	Symbol * sym = m_st->lookup(name);
	Basetype symType = sym->m_basetype;
	if(symType != expected){
	  this->t_error(ret_type_mismatch, p->m_attribute);
	}
      }
      //print_type(expected);
      //printf("  ");
      //print_type(actual);
      if(expected != actual){
	this->t_error(ret_type_mismatch, p->m_attribute);
	}
    }

    // Check that the declared return type is not an array
    void check_return(Return *p)
    {
      Basetype ret = p->m_expr->m_attribute.m_basetype;

      if(ret == bt_string){
	this->t_error(ret_type_mismatch, p->m_attribute);
      }
    }

    // Create a symbol for the procedure and check there is none already
    // existing
    void check_call(Call *p)
    {
      Symbol *sym = m_st->lookup(p->m_symname->spelling());
      //Check it exists
      if(sym == NULL){
	this->t_error(proc_undef, p->m_attribute);
      }
      const char* lhsid = lhs_to_id(p->m_lhs);
      Symbol* s = m_st->lookup(lhsid);
      if(s == NULL){
	this->t_error(var_undef, p->m_lhs->m_attribute);
      }

      //Check that lhs and rhs types are equivalent
      Basetype expected = s->m_basetype;
      Basetype actual = sym->m_return_type;
      //print_type(expected);
      //print_type(actual);
      if(expected != actual){
	this->t_error(call_type_mismatch, p->m_attribute);
      }
      //Check that the number of params are equal
      int paramSizeExpected = p->m_expr_list->size();
      int paramSizeActual = sym->m_arg_type.size();
      if(paramSizeExpected != paramSizeActual){
	this->t_error(narg_mismatch, p->m_attribute);
      }
      //STILL NEED TO CHECK IF TYPES OF PARAMS MATCH
      std::list<Expr_ptr>::iterator iter;
      iter = p->m_expr_list->begin();
      int argSize = sym->m_arg_type.size();

      for(int i =0; i < argSize; i++){
	if(sym->m_arg_type[i] != (*iter)->m_attribute.m_basetype)
	  this->t_error(call_type_mismatch, (*iter)->m_attribute);
	iter++;
      }
    }

    // For checking that this expressions type is boolean used in if/else
    void check_pred_if(Expr* p)
    {
      Basetype t = p->m_attribute.m_basetype;
      //print_type(t);
      if(t != bt_boolean){
	this->t_error(ifpred_err, p->m_attribute);
      }
    }

    // For checking that this expressions type is boolean used in while
    void check_pred_while(Expr* p)
    {
      Basetype t = p->m_attribute.m_basetype;
      if(t != bt_boolean){
	this->t_error(whilepred_err, p->m_attribute);
      }
    }


  const char* lhs_to_id(Lhs* lhs)
  {
    Variable *v = dynamic_cast<Variable*>(lhs);
    if(v) {
      return v->m_symname->spelling();
    }
  }

    void check_assignment(Assignment* p)
    {
      Basetype right = p->m_expr->m_attribute.m_basetype;
      const char* lhs_name = lhs_to_id(p->m_lhs);
      Symbol *sym = m_st->lookup(lhs_name);
      Basetype left = sym->m_basetype;
      //print_type(left);
      //print_type(right);
      /*if(right == bt_integer){
	printf("right is int");
	}*/

      if(left != right){
	if((left != bt_intptr || left != bt_charptr) && right != bt_ptr){
	  this->t_error(incompat_assign, p->m_attribute);
	}
      }
    }

    void check_string_assignment(StringAssignment* p)
    {
      const char* lhs_name = lhs_to_id(p->m_lhs);
      Symbol *sym = m_st->lookup(lhs_name);
      Basetype left = sym->m_basetype;
      //Basetype left = p->m_lhs->m_attribute.m_basetype;
      if (left != bt_string){
	this->t_error(incompat_assign, p->m_attribute);
      }
    }

    void check_array_access(ArrayAccess* p)
    {
      Symbol *sym;
      const char* name = p->m_symname->spelling();
      sym = m_st->lookup(name);
      Basetype symType = sym->m_basetype;
      Basetype exprType = p->m_expr->m_attribute.m_basetype;
      if(sym == NULL){
	this->t_error(var_undef, p->m_attribute);
      }
      if(symType != bt_string){
	this->t_error(no_array_var, p->m_attribute);
      }
      if(exprType != bt_integer){
	this->t_error(array_index_error, p->m_attribute);
      }
      p->m_attribute.m_basetype = bt_char;
    }

    void check_array_element(ArrayElement* p)
    {
      Symbol *sym;
      const char* name = p->m_symname->spelling();
      sym = m_st->lookup(name);
      Basetype symType = sym->m_basetype;
      Basetype exprType = p->m_expr->m_attribute.m_basetype;
      if(sym == NULL){
	this->t_error(var_undef, p->m_attribute);
      }
      if(symType != bt_string){
	this->t_error(no_array_var, p->m_attribute);
      }
      if(exprType != bt_integer){
	this->t_error(array_index_error, p->m_attribute);
      }
      p->m_attribute.m_basetype = bt_char;
    }

    // For checking boolean operations(and, or ...)
    void checkset_boolexpr(Expr* parent, Expr* child1, Expr* child2)
    {
      Basetype child1Type = child1->m_attribute.m_basetype;
      Basetype child2Type = child2->m_attribute.m_basetype;
      if(child1Type != bt_boolean || child2Type != bt_boolean){
	this->t_error(expr_type_err, parent->m_attribute);
      }
      parent->m_attribute.m_basetype = bt_boolean;
    }

    // For checking arithmetic expressions(plus, times, ...)
    void checkset_arithexpr(Expr* parent, Expr* child1, Expr* child2)
    {
      Basetype child1Type = child1->m_attribute.m_basetype;
      Basetype child2Type = child2->m_attribute.m_basetype;
      //print_type(child2Type);
      if(child1Type == bt_charptr){
	//printf("child1 is bt_charptr ");
	if(child2Type != bt_integer){
	  this->t_error(expr_type_err, parent->m_attribute);
	}
	parent->m_attribute.m_basetype = bt_charptr;
	return;
      }
      else if(child1Type != bt_integer || child2Type != bt_integer){
	this->t_error(expr_type_err, parent->m_attribute);
      }
      parent->m_attribute.m_basetype = bt_integer;
    }

    // Called by plus and minus: in these cases we allow pointer arithmetics
    void checkset_arithexpr_or_pointer(Expr* parent, Expr* child1, Expr* child2)
    {
      Basetype child1Type = child1->m_attribute.m_basetype;
      Basetype child2Type = child2->m_attribute.m_basetype;
      //print_type(child1Type);
      //print_type(child2Type);
      if(child1Type == bt_charptr){
	if(child2Type != bt_integer){
	  this->t_error(expr_pointer_arithmetic_err, parent->m_attribute);
	}
      }
      else if(child2Type == bt_charptr){
	if(child1Type != bt_integer){
	  this->t_error(expr_pointer_arithmetic_err, parent->m_attribute);
	}
      }
      else if(child1Type != bt_integer && child2Type != bt_integer){
	this->t_error(expr_type_err, parent->m_attribute);
      }
      else{
	parent->m_attribute.m_basetype = bt_charptr;
      }
    }

    // For checking relational(less than , greater than, ...)
    void checkset_relationalexpr(Expr* parent, Expr* child1, Expr* child2)
    {
      Basetype child1Type = child1->m_attribute.m_basetype;
      Basetype child2Type = child2->m_attribute.m_basetype;
      if(child1Type != bt_integer || child2Type != bt_integer){
	this->t_error(expr_type_err, parent->m_attribute);
      }
      parent->m_attribute.m_basetype = bt_boolean;
    }

    // For checking equality ops(equal, not equal)
    void checkset_equalityexpr(Expr* parent, Expr* child1, Expr* child2)
    {
      Basetype child1Type = child1->m_attribute.m_basetype;
      Basetype child2Type = child2->m_attribute.m_basetype;
      if(child1Type == bt_integer){
	if(child2Type != bt_integer){
	  this->t_error(expr_type_err, parent->m_attribute);
	}
      }
      else if(child1Type == bt_boolean){
	if(child2Type != bt_boolean){
	  this->t_error(expr_type_err, parent->m_attribute);
	}
      }
      else if(child1Type == bt_char){
	if(child2Type != bt_char){
	  this->t_error(expr_type_err, parent->m_attribute);
	}
      }
      else if(child1Type == bt_intptr){
	if(child2Type != bt_intptr || child2Type != bt_ptr){
	  this->t_error(expr_type_err, parent->m_attribute);
	}
      }
      else if(child1Type == bt_charptr){
	if(child2Type != bt_charptr || child2Type != bt_ptr){
	  this->t_error(expr_type_err, parent->m_attribute);
	}
      }
      else if(child1Type == bt_ptr){
	if(child2Type != bt_intptr || child2Type != bt_charptr || child2Type != bt_ptr){
	  this->t_error(expr_type_err, parent->m_attribute);
	}
      }
      parent->m_attribute.m_basetype = bt_boolean;
    }

    // For checking not
    void checkset_not(Expr* parent, Expr* child)
    {
      Basetype childType = child->m_attribute.m_basetype;
      if(childType != bt_boolean){
	this->t_error(expr_type_err, parent->m_attribute);
      }
      parent->m_attribute.m_basetype = bt_boolean;
    }

    // For checking unary minus
    void checkset_uminus(Expr* parent, Expr* child)
    {
      Basetype childType = child->m_attribute.m_basetype;
      if(childType != bt_integer){
	this->t_error(expr_type_err, parent->m_attribute);
      }
      parent->m_attribute.m_basetype = bt_integer;
    }

    void checkset_absolute_value(Expr* parent, Expr* child)
    {
      printf("checkset_abs ");
      Basetype childType = child->m_attribute.m_basetype;
      if(childType != bt_integer && childType != bt_string){
	this->t_error(expr_abs_error, parent->m_attribute);
      }
      parent->m_attribute.m_basetype = bt_integer;
    }

    void checkset_addressof(Expr* parent, Lhs* child)
    {
      const char* childName = lhs_to_id(child);
      Symbol *sym = m_st->lookup(childName);
      Basetype childType = sym->m_basetype;
      if(childType == bt_integer){
	parent->m_attribute.m_basetype = bt_intptr;
      }
      else if(childType == bt_char){
	parent->m_attribute.m_basetype = bt_charptr;
      }
      /* NOT SURE ABOUT THIS IMPLEMENTATION OF INDEXED STRINGS */
      else if(childType == bt_string){
	parent->m_attribute.m_basetype = bt_charptr;
      }
      else{
	this->t_error(expr_addressof_error, parent->m_attribute);
      }
    }

    void checkset_deref_expr(Deref* parent,Expr* child)
    {
      Basetype childType = child->m_attribute.m_basetype;
      if(childType == bt_intptr){
	parent->m_attribute.m_basetype = bt_integer;
      }
      else if (childType == bt_charptr){
	parent->m_attribute.m_basetype = bt_char;
      }
      else{
	this->t_error(invalid_deref, parent->m_attribute);
      }
    }

    // Check that if the right-hand side is an lhs, such as in case of
    // addressof
    void checkset_deref_lhs(DerefVariable* p)
    {
      Symbol *sym = m_st->lookup(p->m_symname->spelling());
      Basetype t = sym->m_basetype;

      if(sym == NULL){
	this->t_error(var_undef, p->m_attribute);
      }
      else if(t == bt_intptr){
	p->m_attribute.m_basetype = bt_integer;
      }
      else if(t == bt_charptr){
	p->m_attribute.m_basetype = bt_char;
      }
      else{
	this->t_error(invalid_deref, p->m_attribute);
      }
    }

    void checkset_variable(Variable* p)
    {
      Symbol *sym = m_st->lookup(p->m_symname->spelling());
      if(sym == NULL){
	this->t_error(var_undef, p->m_attribute);
      }
    }

    void checkset_ident(Ident* p){
      Symbol *sym;
      sym = m_st->lookup(p->m_symname->spelling());
      if(sym == NULL){
        t_error(var_undef, p->m_attribute);
      }
	p->m_attribute.m_basetype = sym->m_basetype;
    }

  public:

    Typecheck(FILE* errorfile, SymTab* st) {
        m_errorfile = errorfile;
        m_st = st;
    }

    void visitProgramImpl(ProgramImpl* p)
    {
      default_rule(p);
      check_for_one_main(p);
      FILE file;
      FILE *f = &file;
      f = fopen("output.txt", "w");
      m_st->dump(f);
    }

    void visitProcImpl(ProcImpl* p)
    {
      m_st->open_scope();
      char* main = (char*)"Main";
      if(m_st->exist(main)){
	printf("Main exists");
	mainCount++;
      }
      default_rule(p);
      m_st->close_scope();
      add_proc_symbol(p);
      check_proc(p);
    }

    void visitCall(Call* p)
    {
      default_rule(p);
      check_call(p);
    }

    void visitNested_blockImpl(Nested_blockImpl* p)
    {
      default_rule(p);
    }

    void visitProcedure_blockImpl(Procedure_blockImpl* p)
    {
      default_rule(p);
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
      checkset_ident(p);
    }

    void visitReturn(Return* p)
    {
      default_rule(p);
      check_return(p);
    }

    void visitIfNoElse(IfNoElse* p)
    {
      default_rule(p);
      check_pred_if(p->m_expr);
    }

    void visitIfWithElse(IfWithElse* p)
    {
      default_rule(p);
      check_pred_if(p->m_expr);
    }

    void visitWhileLoop(WhileLoop* p)
    {
      default_rule(p);
      check_pred_while(p->m_expr);
    }

    void visitCodeBlock(CodeBlock *p)
    {
      m_st->open_scope();
      default_rule(p);
      m_st->close_scope();
    }

    void visitTInteger(TInteger* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_integer;
    }

    void visitTBoolean(TBoolean* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_boolean;
    }

    void visitTCharacter(TCharacter* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_char;
    }

    void visitTString(TString* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_string;
      p->m_attribute.stringLen = p->m_primitive->m_data;
    }

    void visitTCharPtr(TCharPtr* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_charptr;
    }

    void visitTIntPtr(TIntPtr* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_intptr;
    }

    void visitAnd(And* p)
    {
      default_rule(p);
      checkset_boolexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitDiv(Div* p)
    {
      default_rule(p);
      checkset_arithexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitCompare(Compare* p)
    {
      default_rule(p);
      checkset_equalityexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitGt(Gt* p)
    {
      default_rule(p);
      checkset_relationalexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitGteq(Gteq* p)
    {
      default_rule(p);
      checkset_relationalexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitLt(Lt* p)
    {
      default_rule(p);
      checkset_relationalexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitLteq(Lteq* p)
    {
      default_rule(p);
      checkset_relationalexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitMinus(Minus* p)
    {
      default_rule(p);
      checkset_arithexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitNoteq(Noteq* p)
    {
      default_rule(p);
      checkset_equalityexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitOr(Or* p)
    {
      default_rule(p);
      checkset_boolexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitPlus(Plus* p)
    {
      default_rule(p);
      checkset_arithexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitTimes(Times* p)
    {
      default_rule(p);
      checkset_arithexpr(p,p->m_expr_1,p->m_expr_2);
    }

    void visitNot(Not* p)
    {
      default_rule(p);
      checkset_not(p,p->m_expr);
    }

    void visitUminus(Uminus* p)
    {
      default_rule(p);
      checkset_uminus(p,p->m_expr);
    }

    void visitArrayAccess(ArrayAccess* p)
    {
      default_rule(p);
      check_array_access(p);
    }

    void visitIntLit(IntLit* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_integer;
    }

    void visitCharLit(CharLit* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_char;
    }

    void visitBoolLit(BoolLit* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_boolean;
    }

    void visitNullLit(NullLit* p)
    {
      default_rule(p);
      p->m_attribute.m_basetype = bt_ptr;
    }

    void visitAbsoluteValue(AbsoluteValue* p)
    {
      printf("VISIT ABSVALUE");
      default_rule(p);
      checkset_absolute_value(p,p->m_expr);
    }

    void visitAddressOf(AddressOf* p)
    {
      default_rule(p);
      checkset_addressof(p,p->m_lhs);
    }

    void visitVariable(Variable* p)
    {
      default_rule(p);
      checkset_variable(p);
    }

    void visitDeref(Deref* p)
    {
      default_rule(p);
      checkset_deref_expr(p,p->m_expr);
    }

    void visitDerefVariable(DerefVariable* p)
    {
      default_rule(p);
      checkset_deref_lhs(p);
    }

    void visitArrayElement(ArrayElement* p)
    {
      default_rule(p);
      check_array_element(p);
    }

    // Special cases
  void visitPrimitive(Primitive* p)
  {
  }
  void visitSymName(SymName* p)
  {
  }
  void visitStringPrimitive(StringPrimitive* p)
  {
  }
};


void dopass_typecheck(Program_ptr ast, SymTab* st)
{
    Typecheck* typecheck = new Typecheck(stderr, st);
    ast->accept(typecheck); // Walk the tree with the visitor above
    delete typecheck;
}
