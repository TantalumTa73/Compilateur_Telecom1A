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

Variable find_var(std::string var_name){
    v_cout << "||||||||||||||||||||entering in find_var\n";
    v_cout << "  called_contexts' size : " ;
    v_cout << std::to_string(called_contexts.size()) << "\n"; 
    // to begin with the last called section
    for (auto it = called_contexts.rbegin(); 
        it != called_contexts.rend(); it ++){

        if (contexts[*it].vars.find(var_name) != contexts[*it].vars.end()){
            v_cout << "  " << var_name << "'s offset : " ;
            v_cout << std::to_string(contexts[*it].vars[var_name].offset) ;
            v_cout << " in (compiler.cpp)\n";
            return contexts[*it].vars[var_name];
        }
    }

    v_cout << "  " << var_name << " not found (compiler.cpp)\n";
    return Variable();
}

///////////////////////////////////////////////////////////

Context::Context() {
    vars = unordered_map<string, Variable>();
    var_offset = -1 * SIZE;
    arg_offset = 2 * SIZE;
    return ;
}

Context::Context(string name_)
: name(name_) {
    vars = unordered_map<string, Variable>();
    var_offset = -1 * SIZE;
    arg_offset = 2 * SIZE;
    return ;
}

void Context::init_var(string var_name, bool is_arg) {
    if (auto search = vars.find(var_name); search != vars.end()) {
        return;
    }
    int offset = is_arg ? arg_offset : var_offset;
    Variable new_var = Variable(var_name, name, offset, is_arg);
    vars.insert({var_name, new_var});
    v_cout << var_name << "'s offset in " << name << " : " ;
    v_cout << to_string(offset) << "(Contexts.cpp) \n";
    if (is_arg) {
        arg_offset += SIZE;
    } else {
        var_offset -= SIZE;
    }
    return;
}