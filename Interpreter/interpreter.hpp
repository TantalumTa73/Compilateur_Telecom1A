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
        Token root ;
        Token actual_token ;
        std::string actual_function ; 
        std::unordered_map<std::string, int> gvar ;
        std::unordered_map<std::string, Function> functions ;

        int get_value(Token token) ;

        int get_var(std::string var_name) ;
        void set_var(std::string var_name, int value) ;
        void call_function();

};