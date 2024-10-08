#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "../Interpreter/token.hpp"

struct Variable {

    public:
        std::string name;
        int val;
};

class Function {

    public:

        const std::string name;
        const std::vector<Token> body;
        int nb_layer; // the root's layer is 0, then main's layer is 1, etc... 

        Function();
        Function(std::string name_, std::string arg_, std::vector<Token> body_);

        std::optional<int> get_var(std::string var_name);
        void set_var(std::string var_name, int value);
        int get_nb_var();

    private:
        const std::string arg;
        int depth_shift;
        std::unordered_map<std::string, Variable> vars;
};