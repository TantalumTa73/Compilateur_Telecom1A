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

// inline void var_def_exit(string name, string type, int array_size, string ctx){
//     int size ;
    

//     contexts[ctx].init_var(name, size, false);
//     v_cout << "initialize " << name << " in " << ctx << "\n"; 
// }

void GVarDef::on_exit(){
    // if (array_size != 1)
    throw invalid_argument("global not implemented");

    // var_def_exit(name, type, array_size, called_contexts.back());
    w_init_global_var(name);
}
void SvarDef::on_exit(){
    // if (array_size != 1)
    //     throw invalid_argument("array not implemented");

    // int size = get_size();
    int size = SIZE_INT * array_size ;

    // var_def_exit(name, type, size, );

    string var_name = array_size == 1 ? name : name + "[" + "]";

    contexts[called_contexts.back()].init_var(var_name, size, false);
    v_cout << "initialize " << type << " " << name ;
    if (array_size != 1) v_cout << "[" << array_size << "]" ;
    v_cout << " in " << called_contexts.back() ;
    v_cout << " (" << size << ")\n";

    w_init_var(size);
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
        contexts[name].init_var(arg->name, 8, true);
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
    // v_cout << variable_buffer.name << "'s function is : " << variable_buffer.fun_name << "\n";
    // v_cout << "  " << variable_buffer.name << "'s offset : " << variable_buffer.offset << "\n";
    w_set_var(left_value->get_address(),op);

}


// GET_VAR --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ValueGet::on_exit(){
    w_push_var(value->get_address());
}

// CST --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Int::on_enter(){
    w_push_cst(value);
}


// OP --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LeftValOp::on_exit(){
    w_left_val_op(op,left_value->get_address());
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