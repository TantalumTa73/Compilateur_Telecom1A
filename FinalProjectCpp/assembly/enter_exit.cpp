#include "../token.hpp"
#include "../context.hpp"
#include "../write_assembly.hpp"

#include "../subclasses/arg.hpp"
#include "../subclasses/expr.hpp"
#include "../subclasses/gstmt.hpp"
#include "../subclasses/left_val.hpp"
#include "../subclasses/litteral.hpp"
#include "../subclasses/root.hpp"
#include "../subclasses/stmt.hpp"

void Sreturn::on_exit(){
    w_ret(called_contexts.back() == MAIN);
}

// DEF_VAR --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void GVarDef::on_exit(){
    contexts[called_contexts.back()].init_var(name, false);
    v_cout << "initialize " << name << " in " << called_contexts.back() << "\n"; 
    v_cout << "called_contexts' size :  " << to_string(called_contexts.size());
    w_init_global_var(name);
}
void SvarDef::on_exit(){
    contexts[called_contexts.back()].init_var(name, false);
    v_cout << "initialize " << name << " in " << called_contexts.back() << "\n"; 
    v_cout << "called_contexts' size :  " << to_string(called_contexts.size());
    w_init_var();
}


// DEF_FUNCTION --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GFunDef::on_enter(){
    v_cout << "defining " << name << " function\n";
    Context f = Context(name);
    contexts.insert({name, f});

    called_contexts.push_back(name);
    v_cout << "called_contexts' back : " << called_contexts.back() << "\n" ;
    v_cout << "called_contexts' back : " << called_contexts.back() << "\n" ;

    if (name == GLOBAL) { return; }

    w_init_f(name);

    for (auto arg : args){
        contexts[name].init_var(arg->name, true);
    }
}

void GFunDef::on_exit(){
    // avoid a function that doesn't have return
    w_ret(called_contexts.back() == MAIN);
    called_contexts.pop_back();
}


// CALL_FUN --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void FunCall::on_enter(){
    if (auto search = contexts.find(name); search == contexts.end()){
        v_cout << name << " unknown in contexts";
        throw invalid_argument("unknown function");
    }
}

void FunCall::on_exit(){
    w_call_function(name);
}


// SET_VAR --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void SvarSet::on_exit(){
    if (op != "=")
        throw invalid_argument("op " + op + " is not implemented");
    string name = left_value->get_id();
    Variable variable_buffer = find_var(name);
    v_cout << variable_buffer.name << "'s function is : " << variable_buffer.fun_name << "\n";
    if (variable_buffer.fun_name == GLOBAL){
        w_set_global_var(variable_buffer.name);
    } else {
        v_cout << "  " << variable_buffer.name << "'s offset : " << variable_buffer.offset << "\n";
        w_set_var(variable_buffer.offset);
    }
}


// GET_VAR --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void VarGet::on_exit(){
    string name = value->get_id();
    Variable variable_buffer = find_var(name);
    if (variable_buffer.fun_name == GLOBAL){
        w_push_global_var(name);
    } else {
        w_push_local_var(variable_buffer.offset);
    }
}


// CST --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Int::on_enter(){
    w_push_cst(value);
}


// OP --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LeftValOp::on_exit(){
    w_left_val_op(op);
}
void Uniop::on_exit(){
    w_uniop(uniop);
}
void Binop::on_exit(){
    w_binop(binop);
}
void Ternop::on_exit(){
    w_ternop();
}


// To Implement --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Sfor::on_enter(){
    throw invalid_argument("for not implemented");
}
void Swhile::on_enter(){
    throw invalid_argument("while not implemented");
}
void Sif::on_enter(){
    throw invalid_argument("if not implemented");
}
void SifElse::on_enter(){
    throw invalid_argument("if else not implemented");
}