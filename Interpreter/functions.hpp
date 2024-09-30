#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "simplified_token.hpp"

class Function : public FunctionDef{

    public:

        int layer; // Only for compiler

        Function() ;
        Function(FunctionDef f) ;

        std::optional<int> get_var(std::string var_name);
        void set_var(std::string var_name, int value);

    private:
        std::unordered_map<std::string, int> vars;
};