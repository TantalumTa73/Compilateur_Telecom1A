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
    w_ret(called_contexts.back() == MAIN, value != nullptr);
}

// DEF_VAR -----------------------------

void GVarDef::on_exit(){
    
    int size = type_size(type);
    for (auto d : array_size) size *= d;

    contexts[GLOBAL].init_var(name, size, false);
    w_init_global_var(name, size);
}
void SvarDef::on_exit(){
    // if (array_size != 1)
    //     ERROR("array not implemented");

    int size = type_size(type);
    for (auto d : array_size) size *= d;

    int address = (value == nullptr) ? 0 : contexts[called_contexts.back()].var_offset;
    contexts[called_contexts.back()].init_var(name, size, false);

    w_init_var(size,address);
}


// DEF_FUNCTION SCOPE -----------------------------

void GFunDef::on_enter(){
    // v_cout << "defining function " << name << "\n";
    Context f = Context(name);
    contexts.insert({name, f});

    called_contexts.push_back(name);
    // v_cout << "called_contexts' back : " << called_contexts.back() << "\n" ;

    if (name == GLOBAL) { return; }

    w_init_f(name);

    for (auto arg : args){
        string var_name = arg->name ;
        int size = SIZE_INT ;
        contexts[name].init_var(var_name, size, true);
    }
}

void Sscope::on_enter(){
    // v_cout << "defining scope " << name << "\n";

    called_contexts.push_back(name);

    // check if name already defined
    if (contexts.find(name) != contexts.end()){
        // v_cout << name << " already defined in contexts\n";
        return ;
    }

    add_line("scope: " + name, true, true);
    int offset = contexts[ctx].var_offset + SIZE_INT ;
    v_cout << "new ctx " << name << " in " << ctx ;
    v_cout << " (" << offset << ")\n" ;
    Context f = Context(name,offset);
    contexts.insert({name, f});

    // if (name == GLOBAL) { return; }
    // w_init_f(name);
}

void GFunDef::on_exit(){
    // avoid a function that doesn't have return
    w_ret(called_contexts.back() == MAIN);
    called_contexts.pop_back();
}

void Sscope::on_exit(){
    add_line("end of scope: " + name, true, true);
    add_line();
    called_contexts.pop_back();
}

// CALL_FUN -----------------------------

void FunCall::on_enter(){
    if (auto search = contexts.find(name); search == contexts.end()){
        ERROR("unknown function " + name);
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

    // v_cout << "Var Set : " << value->tk_type << "\n"; 
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

// LITTERAL -----------------------------

void Int::on_enter(){
    w_push_cst(value);
}
void Char::on_enter(){
    w_push_cst((int) value);
}
void Bool::on_enter(){
    w_push_cst((int) value);
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
    if (binop == "&&" || binop == "||")
        return ;
    w_binop(binop);
}

void Ternop::on_exit(){
    w_ternop();
}

// Assembly -----------------------------

void CmdX86::on_enter(){
    add_line("Custom x86 cmd", true, true);
    add_line(cmd);
    add_line();
}

void Jz::on_enter(){
    add_line("JZ",true,true);
    add_line("pop %rax");
    add_line("cmp $0, %rax");
    add_line("jz "+label);
    add_line();
}
void Jnz::on_enter(){
    add_line("JNZ",true,true);
    add_line("pop %rax");
    add_line("cmp $0, %rax");
    add_line("jnz "+label);
    add_line();
}
void Jmp::on_enter(){
    add_line("JMP",true,true);
    add_line("jmp "+label);
    add_line();
}

void Label::on_enter(){
    // add_line("Label",true,true);
    add_line(label+":",false);
    add_line();
}

// To Implement -----------------------------

void Skeyword::on_enter(){
    if (keyword == "break"){
        // ERROR("Keyword on_enter : break not implemented");
        v_cout << "kw : break\n";
    } else if (keyword == "continue") {
        v_cout << "kw : continue\n";
        // ERROR("Keyword on_enter : continue not implemented");
    } else {
        ERROR("Keyword on_enter : undefined keyword "+ keyword);
    }
}

// void Sfor::on_enter(){
//     ERROR("for not implemented");
// }
// void Swhile::on_enter(){
//     ERROR("while not implemented");
// }
void Sif::on_enter(){
    add_line("Stmt if",true,true);
}

void SifElse::on_enter(){
    add_line("Stmt if-else",true,true);
}