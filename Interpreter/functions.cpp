#include <string>
#include <optional>

#include "functions.hpp"

Function::Function() : 
    name(""), arg(0), body(std::vector<Token>()) {
    arg_value = 0;
    vars = std::unordered_map<std::string, int>();
    return ;
}

Function::Function(std::string name_, std::string arg_, std::vector<Token> body_) : 
    name(name_), arg(arg_), body(body_) {
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