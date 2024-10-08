#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "simplified_token.hpp"

class Function {

    public:

        std::string fun_name ;
        std::string arg_name ;
        std::vector<TkPtr> body ;

        int layer; // Only for compiler

        Function() ;
        Function(FunctionDef &f) ;

        std::optional<int> get_var(std::string var_name);
        void set_var(std::string var_name, int value);

    private:
        std::unordered_map<std::string, int> vars;
};