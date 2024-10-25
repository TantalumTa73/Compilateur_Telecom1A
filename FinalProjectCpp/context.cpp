#include "context.hpp"

unordered_map<string, Context> contexts = unordered_map<string, Context>();
vector<string> called_contexts = vector<string>();

Variable::Variable(){
    name = "";
    fun_name = "";
    offset = 0;
    is_arg = false;
}

Variable::Variable(string name, string fun_name, int offset, bool is_arg){
    this->name = name ;
    this->fun_name = fun_name ;
    this->offset = offset;
    this->is_arg = is_arg ;
}

string Variable::get_adress(){
    if (fun_name == GLOBAL){
        return name + "(%rip)";
    } else {
        return to_string(offset) + "(%rbp)";
    }
}

Variable find_var(string var_name){
    
    v_cout << "find_var : " << var_name << "\n";
    
    for (auto it = called_contexts.rbegin(); 
        it != called_contexts.rend(); it ++){

        if (contexts[*it].vars.find(var_name) != contexts[*it].vars.end()){
            return contexts[*it].vars[var_name];
        }
    }

    v_cout << "  " << var_name << " not found (compiler.cpp)\n";
    return Variable();
}

///////////////////////////////////////////////////////////

Context::Context() {
    vars = unordered_map<string, Variable>();
    var_offset = -1 * SIZE_INT;
    arg_offset = 2 * SIZE_INT;
    return ;
}

Context::Context(string name_)
: name(name_) {
    vars = unordered_map<string, Variable>();
    var_offset = -1 * SIZE_INT;
    arg_offset = 2 * SIZE_INT;
    return ;
}

void Context::init_var(string var_name, int size, bool is_arg) {
    if (auto search = vars.find(var_name); search != vars.end()) {
        return;
    }
    int offset = is_arg ? arg_offset : var_offset;
    Variable new_var = Variable(var_name, name, offset, is_arg);
    vars.insert({var_name, new_var});
    
    if (is_arg) {
        arg_offset += size;
    } else {
        var_offset -= size;
    }
    return;
}