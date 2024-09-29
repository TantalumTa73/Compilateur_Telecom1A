#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "token.hpp"

class Function {

    public:

        const std::string name;
<<<<<<< HEAD
        const std::vector<Token> body;
        int arg_value;
=======
        const int layer;
>>>>>>> e17db6d (compiler in progress...)

        Function() ;
        Function(std::string name_, std::string arg_, std::vector<Token> body_) ;

        std::optional<int> get_var(std::string var_name);
        void set_var(std::string var_name, int value);

    private:
        const std::string arg;
        std::unordered_map<std::string, int> vars;
};