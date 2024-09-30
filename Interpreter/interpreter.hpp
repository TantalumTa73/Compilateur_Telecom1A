#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "token.hpp"
#include "functions.hpp"


class Interpreter {

    public:

        Interpreter();
        Interpreter(Token root) ;

        void run() ;

    private:
        int last_value ;

        Token actual_token ;
        std::string actual_function ;

        std::vector<Token> stack;
        std::vector<std::string> stack_context;

        std::unordered_map<std::string, Function> functions ;

        int get_value(Token token) ;

        int get_var(std::string var_name) ;
        void set_var(std::string var_name, int value) ;
        void def_var(std::string var_name);
        void call_function(std::string function_name, int arg) ;

};