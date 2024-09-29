#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <fstream>

#include "compiler.hpp"
#include "../Interpreter/token.hpp"
#include "../Interpreter/functions.hpp"

Compiler::Compiler() {
    root = Token();
    registers_name = std::unordered_map<int, std::string>();
    functions = std::unordered_map<std::string, Function>();
    return;
}

Compiler::Compiler(Token root_, std::string cfilename_) {
    root = root_;
    cfilename = cfilename_;
    gvar = std::unordered_map<std::string, int>();
    functions = std::unordered_map<std::string, Function>(); 
    return;
}

void Compiler::w_init(){
    file << "   section .text\n";
    file << "   global main\n";
    file << "\n";
    file << "main:\n";
}

void Compiler::w_init_var()

void Compiler::w_set_var(std::string str){

}

void Compiler::w_print(std::string){
    file << "\n"; 
    file << "\n"; 
    file << "\n"; 
}

void Compiler::run(){
    std::string sfilename = cfilename.substr(0, cfilename.size()) + ".s";
    file.open(sfilename, std::ios::out);
    w_init();

    std::vector<Token> stack;
    stack.push_back(root);

    actual_function = "main";

    while (stack.size() > 0) {
        actual_token = stack.back();
        stack.pop_back();

        if (actual_token.get_attribute("name") == "__root__"){
            reverse(actual_token.childs.begin(), actual_token.childs.end());
            for (Token t : actual_token.childs) stack.push_back(t);
            reverse(actual_token.childs.begin(), actual_token.childs.end());

        } else if (actual_token.get_attribute("action") == "gvardef"){
            std::string var_name = actual_token.get_attribute("name");
            gvar[var_name] = 0;
        }
    }
    file << "ret";
    file.close();
}