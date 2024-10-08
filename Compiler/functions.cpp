#include <string>
#include <optional>

#include "functions.hpp"

Function::Function() : 
    name(""), arg(0), body(std::vector<Token>()) {
    set_var("", 0);
    vars = std::unordered_map<std::string, Variable>();
    depth_shift = 0;
    return ;
}

Function::Function(std::string name_, std::string arg_, std::vector<Token> body_) : 
    name(name_), arg(arg_), body(body_) {
    set_var(arg_, 0);
    vars = std::unordered_map<std::string, Variable>();
    depth_shift = 0;
    return ;
}

int Function::get_nb_var() {
    return vars.size();
}

std::optional<int> Function::get_var(std::string var_name) {
    if (auto search = vars.find(var_name); search != vars.end()) {
        return vars[var_name].val;
    } else {
        return std::nullopt;;
    }
}

void Function::set_var(std::string var_name, int value) {
    if (auto search = vars.find(var_name); search != vars.end()) {
       vars[var_name].val = value; 
    }
    else {
        Variable new_var;
        new_var.name = var_name;
        new_var.val = value;
        new_var.depth_shift = depth_shift; 
        vars.insert({var_name, new_var});
        depth_shift -= 8;
    }
    return;
}