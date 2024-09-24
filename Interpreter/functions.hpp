#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "token.hpp"

class Function {

    public:

        const std::string name;

        Function(){} ;
        Function(std::string name_, std::string arg_);

        std::optional<int> get_var(std::string var_name);
        void set_var(std::string var_name, int value);

    private:
        const std::string arg;
        int arg_value;
        std::unordered_map<std::string, int> vars;
};