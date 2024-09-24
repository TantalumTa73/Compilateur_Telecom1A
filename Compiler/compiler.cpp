#pragma once

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
    gvar = std::unordered_map<std::string, int>();
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

void Compiler::update(){
    //write on the file.s
}

void Compiler::run(){
    std::ofstream file;
    std::string sfilename = cfilename.replace(cfilename.size() - 1, 1, "s");
    file.open(sfilename, std::ios::out);


    std::vector<Token> stack;
    stack.push_back(root);

    actual_function = "__root__";

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

    file.close();
}