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
        std::vector<int> last_values ;

        Token actual_token ;
        std::string actual_function ;

        std::vector<Token> stack;
        std::vector<std::string> stack_context;

        std::unordered_map<std::string, Function> functions ;

        void get_value(Token token) ;

        void get_var(std::string var_name) ;
        void set_var(std::string var_name) ;
        void def_var(std::string var_name);
        void call_function(std::string function_name) ;

        void push(int value) ;
        int pop() ;

};