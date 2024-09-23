#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "token.hpp"

class Interpreter {

    public:

        Interpreter();
        Interpreter(Token root) ;

        void run() ;

    // private:
        Token root ;
        std::unordered_map<std::string, int> variables ;
};