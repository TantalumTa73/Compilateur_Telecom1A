#pragma once 
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

#include "../Interpreter/token.hpp"
#include "../Interpreter/functions.hpp"

class Compiler {
    public:

        Compiler();
        Compiler(Token root_, std::string cfilename_);

        void run();

    private:
        std::ofstream file;
        Token root;
        Token actual_token;
        std::string actual_function;
        std::string cfilename;
        std::unordered_map<int, std::string> registers_name;
        std::unordered_map<std::string, Function> functions;
        std::vector<int> active_registers; 
        int nb_children;

        void w_init();
        void w_print(std::string str);
        void w_init_var(std::string str);
        void w_set_var(std::string str, int value);
        void w_arithm();
};