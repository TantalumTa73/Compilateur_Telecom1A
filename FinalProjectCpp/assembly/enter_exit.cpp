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

// DEF_VAR -----------------------------

// inline void var_def_exit(string name, string type, int array_size, string ctx){
//     int size ;
    

//     contexts[ctx].init_var(name, size, false);
//     v_cout << "initialize " << name << " in " << ctx << "\n"; 
// }

void GVarDef::on_exit(){
    // if (array_size != 1)
    ERROR("global not implemented");

    // var_def_exit(name, type, array_size, called_contexts.back());
    w_init_global_var(name);
}
void SvarDef::on_exit(){
    // if (array_size != 1)
    //     ERROR("array not implemented");

    int size ;
    switch (type){
        case INT: size = SIZE_INT; break;
        case CHAR: size = SIZE_CHAR; break;
        case PTR: size = SIZE_PTR; break;
        default: ERROR("unknown type");
    }
    for (auto d : array_size) size *= d;

    contexts[called_contexts.back()].init_var(name, size, false);
    v_cout << "initialize " << type << " " << name ;
    v_cout << " in " << called_contexts.back() ;
    v_cout << " (" << size << ")\n";

    w_init_var(size);
}


// DEF_FUNCTION -----------------------------

void GFunDef::on_enter(){
    // v_cout << "defining " << name << " function\n";
    Context f = Context(name);
    contexts.insert({name, f});

    called_contexts.push_back(name);
    // v_cout << "called_contexts' back : " << called_contexts.back() << "\n" ;

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


// CALL_FUN -----------------------------

void FunCall::on_enter(){
    if (auto search = contexts.find(name); search == contexts.end()){
        v_cout << name << " unknown in contexts";
        ERROR("unknown function");
    }
}

void FunCall::on_exit(){
    w_call_function(name);
}


// SET_VAR -----------------------------

void SvarSet::on_exit(){
    // v_cout << variable_buffer.name << "'s function is : " << variable_buffer.fun_name << "\n";
    // v_cout << "  " << variable_buffer.name << "'s offset : " << variable_buffer.offset << "\n";
    // w_set_var(left_value->get_address(),op);

    v_cout << "Var Set : " << value->tk_type << "\n"; 
    if (value->tk_type == LIST){
        List* list = (List*)value;
        add_line("set to list " + to_string(list->values.size()), true, true);
        // for (auto v : list->values){
        // }
    } else {
        w_set_var(op);
    }
}


// GET_VAR -----------------------------

void ValueGet::on_exit(){
    // w_push_var(value->get_address());
    w_push_var();
}

void List::on_enter(){
    add_line("list " + to_string(values.size()), true, true);
}

// CST -----------------------------

void Int::on_enter(){
    w_push_cst(value);
}


// OP -----------------------------

// LeftValue

void VarGet::on_exit(){
    Variable var = find_var(name);

    w_push_add(var.get_adress());
}

void ArrayGet::on_exit(){
    w_array_get();
}

void LLop::on_exit(){
    if (op == "++x" || op == "--x")
        // w_llop(op, left_value->get_address());
        w_llop(op);
    else
        ERROR(op+" unknown left_val_operators");
}

void RLop::on_exit(){
    w_rlop(op);
}

// Expr

void LRop::on_exit(){
    // w_lrop(op, left_value->get_address());
    w_lrop(op);
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

// Assembly -----------------------------

void Jz::on_enter(){
    add_line("JZ",true,true);
    add_line("pop %rax");
    add_line("cmp $0, %rax");
    add_line("jz "+label);
    add_line();
}

void Jmp::on_enter(){
    add_line("JMP",true,true);
    add_line("jmp "+label);
    add_line();
}

void Label::on_enter(){
    add_line("Label",true,true);
    add_line(label+":",false);
    add_line();
}

// To Implement -----------------------------

void Sfor::on_enter(){
    ERROR("for not implemented");
}
void Swhile::on_enter(){
    ERROR("while not implemented");
}
void Sif::on_enter(){
    w_if();
    // else 

}
void SifElse::on_enter(){
    // ERROR("if else not implemented");
    w_if_else();
}