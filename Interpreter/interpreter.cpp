#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

#include "token.hpp"
#include "interpreter.hpp"


Interpreter::Interpreter() {
    root = Token();
    variables = std::unordered_map<std::string, int>();
    return;
}

Interpreter::Interpreter(Token root_) {
    root = root_;
    variables = std::unordered_map<std::string, int>();
    return;
}



void Interpreter::run() {
    std::cout << "Running interpreter" << std::endl;

    for (Token t : root.childs) t.print();
    std::cout << std::endl;

    std::vector<Token> stack;
    stack.push_back(root);
    Token token_ptr ;

    while (stack.size() > 0) {
        token_ptr = stack.back();
        stack.pop_back();
        for (Token t : token_ptr.childs) stack.push_back(t);

        if (token_ptr.get_attribute("action") == "gvardef"){
            std::string var_name = token_ptr.get_attribute("name");
            std::cout << "Defining global variable " << var_name << std::endl;
            variables[var_name] = 0;
        } else {
            std::cout << "Unknown action: " << token_ptr.get_attribute("action") << std::endl;
        }


    }

    return ;
}














