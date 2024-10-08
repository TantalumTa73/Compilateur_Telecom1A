#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <optional>

#include "compiler.hpp"
#include "../Interpreter/token.hpp"
#include "functions.hpp"
#include "write_assembly.hpp"
#include "data.hpp"

Compiler::Compiler() {
    root = Token();
    registers_name = std::unordered_map<std::string, std::optional<int>>();
    functions = std::unordered_map<std::string, Function>(); 
    return;
}

Compiler::Compiler(Token root_, std::string cfilename_) {
    root = root_;
    cfilename = cfilename_;
    registers_name = std::unordered_map<std::string, std::optional<int>>();
    functions = std::unordered_map<std::string, Function>(); 
    return;
}

void Compiler::init_registers(){
    registers_name.insert({"rax", std::nullopt});
    registers_name.insert({"rbx", std::nullopt});
    registers_name.insert({"rcx", std::nullopt});
    registers_name.insert({"rdx", std::nullopt});
    registers_name.insert({"rsi", std::nullopt});
    registers_name.insert({"rdi", std::nullopt});
    registers_name.insert({"rsp", std::nullopt});
    registers_name.insert({"rbp", std::nullopt});
    registers_name.insert({"r8", std::nullopt});
    registers_name.insert({"r9", std::nullopt});
    registers_name.insert({"r10", std::nullopt});
    registers_name.insert({"r11", std::nullopt});
    registers_name.insert({"r12", std::nullopt});
    registers_name.insert({"r13", std::nullopt});
    registers_name.insert({"r14", std::nullopt});
    registers_name.insert({"r15", std::nullopt});
}

void Compiler::reverse_push_childs(){
    std::vector<Token> body = actual_token.childs;
    reverse(body.begin(), body.end());
    for (Token t : body) { 
        stack.push_back(t);
    }
}

void Compiler::define_function(std::string fun_name){
    Function f = Function(fun_name, actual_token.childs);
    functions.insert({fun_name, f});
    reverse_push_childs();

    w_init_f(fun_name);
    std::string arg_name = actual_token.get_attribute("arg"); 
    f.set_var(arg_name, 0, true);
}

void Compiler::define_variable(std::string var_name){
    functions[actual_function].set_var(var_name, 0, false);
    if (actual_function == GLOBAL) {
        w_init_global_var(var_name);
    } else {
       w_init_var();
    }
}

void Compiler::set_variable(std::string var_name){

}

void Compiler::init_compiling(){
    init_registers();

    define_function(GLOBAL);
    actual_function = GLOBAL;

    std::string sfilename = cfilename.substr(0, cfilename.size()) + ".s";
    file.open(sfilename, std::ios::out);
    w_init_template();
}

void Compiler::call_function(std::string fun_name){
    if (auto search = functions.find(fun_name); search == functions.end()) {
        // throw exception
        return;
    }
    reverse_push_childs();
}

void Compiler::run(){
    stack.push_back(root);
    init_compiling();

    while (stack.size() > 0){
        actual_token = stack.back();
        stack.pop_back();
        std::string token_name = actual_token.get_attribute("name");

        if (actual_token.get_attribute("action") == "gvardef"){
            define_variable(token_name);
        } 
        else if (actual_token.get_attribute("action") == "varset"){
            set_variable(token_name);
        } 
        else if (actual_token.get_attribute("action") == "gfundef"){
            define_function(token_name);
        }
        else if (actual_token.get_attribute("action") == "function"){
            call_function(token_name);
        }
        else if (actual_token.get_attribute("action") == "return"){
            //return_function();
        }

    }

    file << "       xor %rax, %rax\n";
    file << "       ret\n";
    file.close();
}