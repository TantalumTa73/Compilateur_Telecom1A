#include <string>
#include <optional>

#include "functions.hpp"

Function::Function() : 
    FunctionDef(0,0,0,0, "", "", std::vector<SimplifiedToken>()) {}

Function::Function(FunctionDef f) : 
    FunctionDef(f) {}


std::optional<int> Function::get_var(std::string var_name) {
    if (var_name == arg_name && false) {
        // return arg_value;
    } else if (vars.find(var_name) != vars.end()) {
        return vars[var_name];
    } else {
        return std::nullopt;;
    }
}

void Function::set_var(std::string var_name, int value) {
    if (var_name == arg_name && false){
        // arg_value = value;
    } else {
        vars[var_name] = value;
    }
    return ;
}