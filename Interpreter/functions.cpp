#include <string>
#include <optional>

#include "functions.hpp"

Function::Function() : 
    fun_name(""), arg_name(""), body(std::vector<TkPtr>()) {
    layer = 0;
    vars = std::unordered_map<std::string, int>();
}

Function::Function(FunctionDef &f) : 
    fun_name(f.fun_name), arg_name(f.arg_name), body(f.body) {
    layer = 0;
    vars = std::unordered_map<std::string, int>();
}



std::optional<int> Function::get_var(std::string var_name) {
    if (vars.find(var_name) != vars.end()) {
        return vars[var_name];
    } else {
        return std::nullopt;;
    }
}

void Function::set_var(std::string var_name, int value) {
    vars[var_name] = value;
    return ;
}