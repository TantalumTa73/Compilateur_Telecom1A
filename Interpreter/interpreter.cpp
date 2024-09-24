#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>

#include "token.hpp"
#include "interpreter.hpp"
#include "exception.hpp"


Interpreter::Interpreter() {
    root = Token();
    gvar = std::unordered_map<std::string, int>();
    functions = std::unordered_map<std::string, Function>();
    return;
}

Interpreter::Interpreter(Token root_) {
    root = root_;
    gvar = std::unordered_map<std::string, int>();
    functions = std::unordered_map<std::string, Function>();
    return;
}


int Interpreter::get_value(Token token){

    

    return 0;
}


void Interpreter::run() {
    std::cout << "Running interpreter" << std::endl;

    for (Token t : root.childs) t.print();
    std::cout << std::endl;

    std::vector<Token> stack;
    stack.push_back(root);
    Token token ;
    std::string actual_function = "__root__";

    while (stack.size() > 0) {
        token = stack.back();
        stack.pop_back();
        

        if (token.get_attribute("name") == "__root__"){
            continue;

        } else if (token.get_attribute("action") == "gvardef"){
            std::string var_name = token.get_attribute("name");
            std::cout << "Defining global variable " << var_name << std::endl;
            gvar[var_name] = 0;

        } else if (token.get_attribute("action") == "gfundef"){
            std::string fun_name = token.get_attribute("name");
            std::string argument = token.get_attribute("arg");
            
            std::cout << "Defining global function " << fun_name << std::endl;

            Function f = Function(fun_name, argument);
            functions.insert(std::make_pair(fun_name, f));
            actual_function = fun_name;

            reverse(token.childs.begin(), token.childs.end()) ;
            for (Token t : token.childs) stack.push_back(t);
            reverse(token.childs.begin(), token.childs.end()) ;

        } else if (token.get_attribute("action") == "varset"){

            std::string var_name = token.get_attribute("name");

            int value = get_value(token.childs[0]);

            if (functions.find(actual_function) == functions.end()){
                std::string msg = "Function " + actual_function + " not found";
                throw InterpreterException(
                    token.start_line, token.start_char,
                    token.end_line, token.end_char,
                    msg
                );
            } else if (functions[actual_function].get_var(var_name).has_value()){
                std::cout << "Set local variable " << var_name << std::endl;
                functions[actual_function].set_var(var_name, value);
            } else if (gvar.find(var_name) != gvar.end()){
                std::cout << "Set global variable " << var_name << std::endl;
                gvar[var_name] = value;
            } else {
                std::string msg = "Variable " + var_name + " not found";
                throw InterpreterException(
                    token.start_line, token.start_char,
                    token.end_line, token.end_char,
                    msg
                );
            }

        } else {
            std::cout << "Unknown action: " << token.get_attribute("action") ;
            std::cout << " in line " << token.start_line ;
            std::cout << " char " << token.start_char ;
            std::cout << " to line " << token.end_line ;
            std::cout << " char " << token.end_char << std::endl;
        }


    }

    return ;
}














