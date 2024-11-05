#include "context.hpp"

unordered_map<string, Context> contexts = unordered_map<string, Context>();
vector<string> called_contexts = vector<string>();

Variable::Variable(){
    name = "";
    ctx_name = "";
    adress = 0;
    is_arg = false;
    type_size = 0;
    full_size = 0;
    array_size = vector<int>();
}

Variable::Variable(string name, string ctx_name, int adress, bool is_arg, int type_size, vector<int> array_size){
    this->name = name ;
    this->ctx_name = ctx_name ;
    this->adress = adress;
    this->is_arg = is_arg ;
    this->type_size = type_size ;
    
    this->array_size = vector<int>();
    this->full_size = type_size ;
    for (auto it = array_size.rbegin(); it != array_size.rend() ; it++){
        this->array_size.push_back(this->full_size);
        this->full_size *= (*it);
    }

    // // DEBUG PRINT
    // v_cout << "new var : " << name << " in " << ctx_name << " at " << adress ;
    // v_cout << "\n\tarray_size : " ;
    // for (auto i : array_size) v_cout << i << " ";
    // v_cout << "\n\tnew array_size : " ;
    // for (auto i : this->array_size) v_cout << i << " ";
    // v_cout << full_size << "\n";
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

int Context::init_var(string var_name, int type_size, vector<int> array_size, bool is_arg) {
    if (auto search = vars.find(var_name); search != vars.end()) {
        ERROR("Init var : " + var_name + " already defined in " + name + "\n");
        return -1;
    }

    int offset = is_arg ? arg_offset : var_offset;
    Variable new_var = Variable(var_name, name, offset, is_arg, type_size, array_size);
    vars.insert({var_name, new_var});

    v_cout << "Init var " << var_name << " in " << name ;
    v_cout << " at " << offset << "\n" ;
    
    if (is_arg) {
        arg_offset += new_var.full_size;
    } else {
        var_offset -= new_var.full_size;
    }
    // v_cout << "  offsets : " << var_offset << " " << arg_offset << "\n";
    return new_var.full_size;
}
