#include "functions.hpp"

Variable::Variable(){
    name = "";
    fun_name = "";
    offset = 0;
    is_arg = false;
}

Variable::Variable(std::string name, std::string fun_name, int offset, bool is_arg){
    this->name = name ;
    this->fun_name = fun_name ;
    this->offset = offset;
    this->is_arg = is_arg ;
}

Function::Function() {
    vars = std::unordered_map<std::string, Variable>();
    var_offset = -1 * SIZE;
    arg_offset = 2 * SIZE;
    return ;
}

Function::Function(std::string name_)
: name(name_) {
    vars = std::unordered_map<std::string, Variable>();
    var_offset = -1 * SIZE;
    arg_offset = 2 * SIZE;
    return ;
}

int Function::get_nb_var() {
    return vars.size();
}

void Function::init_var(std::string var_name, bool is_arg) {
    if (auto search = vars.find(var_name); search != vars.end()) {
        return;
    }
    int offset = is_arg ? arg_offset : var_offset;
    Variable new_var = Variable(var_name, name, offset, is_arg);
    vars.insert({var_name, new_var});
    std::cout << var_name << "'s offset in " << name << " : " << std::to_string(offset) << "(functions.cpp) \n";
    if (is_arg) {
        arg_offset += SIZE;
    } else {
        var_offset -= SIZE;
    }
    return;
}