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

Compiler::Compiler() {
    root = Token();
    return;
}

Compiler::Compiler(Token root_, std::string cfilename_) {
    root = root_;
    cfilename = cfilename_;
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

void Compiler::init_compiling(){
    registers_name = std::unordered_map<std::string, std::optional<int>>();
    init_registers();

    functions = std::unordered_map<std::string, Function>(); 
    Function global_function = Function("global", "", root.childs);
    functions.insert({"global", global_function});

    std::string sfilename = cfilename.substr(0, cfilename.size()) + ".s";
    file.open(sfilename, std::ios::out);
    w_init_s();
}

int Compiler::depth_function(Function f) {
    return f.get_nb_var() * 8;
}

void Compiler::call_function(std::string fun_name, std::string arg_name, int val){
    if (auto search = functions.find(fun_name); search == functions.end()) {
        // throw exception
        return;
    }
    int depth_f = depth_function(functions[fun_name]);
    w_alloc(depth_f); 
}

void Compiler::run(){
    init_compiling();

    std::vector<Token> stack;
    stack.push_back(root);

    actual_function = "global";

    while (stack.size() > 0) {
        actual_token = stack.back();
        stack.pop_back();

        if (actual_token.get_attribute("name") == "__root__"){
            reverse(actual_token.childs.begin(), actual_token.childs.end());
            for (Token t : actual_token.childs) stack.push_back(t);
            reverse(actual_token.childs.begin(), actual_token.childs.end());

        } else if (actual_token.get_attribute("action") == "gvardef" || actual_token.get_attribute("action") == "varset"){
            std::string var_name = actual_token.get_attribute("name");
            functions[actual_function].set_var(var_name, 0);
        } else if (actual_token.get_attribute("action") == "gfundef") {
            std::string fun_name = actual_token.get_attribute("name");
            std::string arg_name = actual_token.get_attribute("arg");
            Function f = Function(fun_name, arg_name, actual_token.childs);
            functions.insert({fun_name, f});
            w_init_f(fun_name);
        } else if (actual_token.get_attribute("action") == "function") {
            std::string fun_name = actual_token.get_attribute("name");
            call_function(fun_name);
        }
    }
    file << "       xor %rax, %rax\n";
    file << "       ret\n";
    file.close();
}