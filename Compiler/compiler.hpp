#pragma once 
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <optional>

#include "token.hpp"
#include "functions.hpp"

class Compiler {
    public:

        Compiler();
        Compiler(Token root_, std::string cfilename_);

        void run();

    private:
        Token root;
        Token actual_token;
        std::string cfilename;
        std::unordered_map<std::string, std::optional<int>> registers_name;
        std::unordered_map<std::string, Function> functions;
        std::vector<Token> called_tokens;
        std::vector<std::string> called_fun_names;
        std::vector<int> active_registers; 
        std::vector<Token> stack;

        void init_registers();
        void init_compiling();
        void push_children(bool can_reverse); // into the stack
        void call_function(std::string fun_name);
        void define_function(std::string fun_name);
        void define_variable(std::string var_name);
        void push_called_token();
        void pop_called_token();
        void evaluate_expr(Token token, std::string fun_name);

};