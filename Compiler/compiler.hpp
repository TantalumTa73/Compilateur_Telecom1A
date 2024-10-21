#ifndef COMPILER_H
#define COMPILER_H

#include <algorithm>

#include "token.hpp"
#include "json_reader.hpp"

class Compiler {
    public:

        Compiler(std::string cfilename_);

        void run();

    private:
        Token* root;
        Token* actual_token;
        std::string cfilename;
        std::vector<Token*> called_tokens;
        std::vector<Token*> stack;
        //std::unordered_map<std::string, std::optional<int>> registers_name;
        //std::vector<int> active_registers; 

        //void init_registers();
        void init_compiling();
        void reversed_children_push(); // into stack
        void push_called_token();
        void pop_called_token();
        void free_tokens(Token* token);

};
#endif