#include "context.hpp"

unordered_map<string, Context> contexts = unordered_map<string, Context>();
vector<string> called_contexts = vector<string>();

Variable::Variable(){
    name = "";
    ctx_name = "";
    adress = 0;
    is_arg = false;
}

Variable::Variable(string name, string ctx_name, int adress, bool is_arg){
    this->name = name ;
    this->ctx_name = ctx_name ;
    this->adress = adress;
    this->is_arg = is_arg ;
}

string Variable::get_adress(int shift){
    v_cout << "get_adress : " << name << " " << ctx_name << " " << adress << " " << shift << "\n";
    if (ctx_name == GLOBAL && shift == 0){
        return name + "(%rip)";
    } else if (ctx_name == GLOBAL) {
        return name + "+" + to_string(shift) + "(%rip)";
    } else {
        return to_string(adress+shift) + "(%rbp)";
    }
}

Variable find_var(string var_name){
    
    // v_cout << "find_var : " << var_name << "\n";
    // v_cout << "\tctx : " ;
    // for (auto c : called_contexts) v_cout << c << " ";
    // v_cout << "\n";
    
    for (auto it = called_contexts.rbegin(); 
        it != called_contexts.rend(); it ++){
        
        // v_cout << *it << " " ;

        if (contexts[*it].vars.find(var_name) != contexts[*it].vars.end()){
            // v_cout << "\n" ;
            return contexts[*it].vars[var_name];
        }
    }
    // v_cout << "\n" ;

    ERROR("find_var : " + var_name + " not found (compiler.cpp)\n");
    return Variable();
}

///////////////////////////////////////////////////////////

Context::Context() {
    vars = unordered_map<string, Variable>();
    var_offset = -1 * SIZE_INT;
    arg_offset = 2 * SIZE_INT;
    return ;
}

Context::Context(string name_, int offset)
: name(name_) {
    vars = unordered_map<string, Variable>();
    var_offset = offset - 1 * SIZE_INT;
    arg_offset = offset + 2 * SIZE_INT;
    return ;
}

void Context::init_var(string var_name, int size, bool is_arg) {
    if (auto search = vars.find(var_name); search != vars.end()) {
        ERROR("Init var : " + var_name + " already defined in " + name + "\n");
        return;
    }

    int offset = is_arg ? arg_offset : var_offset;
    Variable new_var = Variable(var_name, name, offset, is_arg);
    vars.insert({var_name, new_var});

    v_cout << "Init var " << var_name << " in " << name ;
    v_cout << " at " << offset << "\n" ;
    
    if (is_arg) {
        arg_offset += size;
    } else {
        var_offset -= size;
    }
    // v_cout << "  offsets : " << var_offset << " " << arg_offset << "\n";
    return;
}
