#include <string>
#include <optional>

#include "functions.hpp"

Function::Function(std::string name_, std::string arg_)  : name(name_), arg(arg_){
    arg_value = 0;
    vars = std::unordered_map<std::string, int>();
    return ;
}

std::optional<int> Function::get_var(std::string var_name) {
    if (var_name == arg) {
        return arg_value;
    } else if (vars.find(var_name) != vars.end()) {
        return vars[var_name];
    } else {
        return std::nullopt;;
    }
}

void Function::set_var(std::string var_name, int value) {
    if (var_name == arg){
        arg_value = value;
    } else {
        vars[var_name] = value;
    }
    return ;
}