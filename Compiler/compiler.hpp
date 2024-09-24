#pragma once 
#include <unordered_map>
#include <string>
#include <vector>

#include "../Interpreter/token.hpp"
#include "../Interpreter/functions.hpp"

class Compiler {
    public:

        Compiler();
        Compiler(Token root_, std::string cfilename_);

        void run();

    private:
        Token root;
        Token actual_token;
        std::string actual_function;
        std::string cfilename;
        std::unordered_map<std::string, int> gvar;
        std::unordered_map<std::string, Function> functions;
        int nb_children;

        void w_print();

        void update();

};