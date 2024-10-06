#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "simplified_token.hpp"
#include "functions.hpp"


class Interpreter {

    public:

        Interpreter();
        Interpreter(TkPtr root) ;
        ~Interpreter() = default;

        void run() ;

    private:
        std::vector<int> last_values ;

        TkPtr actual_token ;
        std::string actual_function ;

        std::vector<TkPtr> stack;
        std::vector<std::string> stack_context;

        std::unordered_map<std::string, Function> functions ;

        // List of tokens subclasses
        // VarDef VarSet VarGet
        // FunctionDef FunctionCall 
        // Constant Operator Return

        void print_opt(std::string actual_function, std::string var_name) ;

        void def_var(VarDef token) ;
        void set_var(VarSet token) ;
        void get_var(VarGet token) ;

        void def_function(FunctionDef token) ;
        void call_function(FunctionCall token) ;

        void get_value(Constant token) ;
        void get_value(Operator token) ;
        void get_value(Return token) ;


        void push(int value) ;
        int pop() ;

};