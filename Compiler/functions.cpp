#include <string>
#include <optional>

#include "functions.hpp"
#include "data.hpp"

Function::Function() : 
    name(""), body(std::vector<Token>()) {
    vars = std::unordered_map<std::string, Variable>();
    var_offset = -2 * SIZE;
    arg_offset = SIZE;
    return ;
}

Function::Function(std::string name_, std::vector<Token> body_) : 
    name(name_), body(body_) {
    vars = std::unordered_map<std::string, Variable>();
    var_offset = -2 * SIZE;
    arg_offset = SIZE;
    return ;
}

int Function::get_nb_var() {
    return vars.size();
}

std::optional<Variable> Function::get_var(std::string var_name) {
    if (auto search = vars.find(var_name); search != vars.end()) {
        return vars[var_name];
    } else {
        return std::nullopt;;
    }
}

void Function::set_var(std::string var_name, int value, bool is_arg) {
    if (auto search = vars.find(var_name); search != vars.end()) {
       vars[var_name].val = value; 
    }
    else {
        Variable new_var;
        int offset = is_arg ? arg_offset : var_offset;
        new_var.name = var_name;
        new_var.fun_name = name;
        new_var.val = value;
        new_var.offset = offset;
        new_var.is_arg = is_arg;
        vars.insert({var_name, new_var});

        if (is_arg) {
            arg_offset += SIZE;
        } else {
            var_offset -= SIZE;
        }
    }
    return;
}