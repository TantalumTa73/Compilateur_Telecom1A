#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "token.hpp"

struct Variable {

    public:
        std::string name;
        std::string fun_name;
        int val;
        int offset;
        bool is_arg;
};

class Function {

    public:

        const std::string name;
        const std::vector<Token> body;
        std::unordered_map<std::string, Variable> vars;

        Function();
        Function(std::string name_, std::vector<Token> body_);

        std::optional<Variable> get_var(std::string var_name);
        void set_var(std::string var_name, int value, bool is_arg);
        int get_nb_var();

    private:
        int var_offset;
        int arg_offset;
};