#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <optional>

#include "compiler.hpp"
#include "token.hpp"
#include "functions.hpp"
#include "write_assembly.hpp"
#include "data.hpp"

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
    //registers_name = std::unordered_map<std::string, std::optional<int>>();
    functions = std::unordered_map<std::string, Function>(); 
    called_tokens = std::vector<Token>();
    called_fun_names = std::vector<std::string>();
    active_registers = std::vector<int>();
    stack = std::vector<Token>();
    //init_registers();

    Function empty_f = Function();
    functions.insert({PRINT, empty_f});
    functions.insert({READ, empty_f});
    called_fun_names.push_back(GLOBAL);

    std::string sfilename = cfilename.substr(0, cfilename.size() - 1) + "s";
    init(sfilename);
}

std::optional<Variable> Compiler::get_var(std::string var_name){
    for (auto fun_name : called_fun_names){
        std::optional<Variable> var = functions[fun_name].get_var(var_name);
        if (var != std::nullopt){
            return var;
        }
    }
    return std::nullopt;
}

void Compiler::push_children(bool can_reverse){
    std::vector<Token> body = actual_token.children;
    if (can_reverse)
        reverse(body.begin(), body.end());
    for (Token t : body) { 
        stack.push_back(t);
    }
}

void Compiler::define_function(std::string fun_name){
    Function f = Function(fun_name, actual_token.children);
    functions.insert({fun_name, f});
    // avoid a function that doesn't have return
    Token safe_ret_token = Token();
    safe_ret_token.set_attribute("action", "return");
    safe_ret_token.set_attribute("name", "return");
    stack.push_back(safe_ret_token);
    push_children(true);

    w_init_f(fun_name);
    std::string arg_name = actual_token.get_attribute("arg"); 
    f.set_var(arg_name, 0, true);
}

void Compiler::define_variable(std::string var_name){
    functions[called_fun_names.back()].set_var(var_name, 0, false);
    if (called_fun_names.back() == GLOBAL) {
        w_init_global_var(var_name);
    } else {
       w_init_var();
    }
}

void Compiler::push_called_token(){
    int n = actual_token.children.size();
    actual_token.unpushed_children = n;
    std::cout << actual_token.get_attribute("name") << " has " << std::to_string(n) << "untreated children";
    called_tokens.push_back(actual_token);
    if (n == 0){
        pop_called_token();
        return;
    } else {
    push_children(false);
    }
}

void Compiler::pop_called_token(){
    if (called_tokens.size() <= 0)
        return;
    Token token = called_tokens.back();
    token.unpushed_children -= 1;
    if (token.unpushed_children > 0) {
        return;
    }
    called_tokens.pop_back();
    std::string token_name = token.get_attribute("name");
    if (token.get_attribute("action") == "function"){
        w_call_function(token_name);
    } 
    else if (token.get_attribute("operation") != ""){
        w_op(token.get_attribute("operation"));
    }
    else if (token.get_attribute("action") == "return"){
        w_ret(called_fun_names.back() == "main");
        called_fun_names.pop_back();
    }
    else if (token.get_attribute("action") == "varset")
    {
        if (called_fun_names.back() == GLOBAL){
            w_set_global_var(token_name);
        } else {
            w_set_var(functions[called_fun_names.back()].vars[token_name].offset);
        }
    }
    pop_called_token();
}

void Compiler::call_function(std::string fun_name){
    if (auto search = functions.find(fun_name); search == functions.end()){
        std::cout << fun_name << " unknown <-- call_function";
        return;
    }
    called_fun_names.push_back(fun_name);
    push_called_token();
    if (actual_token.unpushed_children == 0){
        if (fun_name == READ){
            std::optional<Variable> var_opt = get_var(actual_token.children[0].get_attribute("name"));
            if (var_opt == std::nullopt){
                std::cout << actual_token.children[0].get_attribute("name") << " not found <-- call_function\n";
                return;
            }
            w_call_read(fun_name, var_opt.value().offset, var_opt.value().fun_name == GLOBAL); 
        } else {
            std::cout << "calling " << fun_name << "\n";
            w_call_function(fun_name);
        }
    }
}

void Compiler::run(){
    init_compiling();
    stack.push_back(root);
    called_fun_names.push_back(GLOBAL);

    while (stack.size() > 0){
        actual_token = stack.back();
        stack.pop_back();
        std::string token_name = actual_token.get_attribute("name");
        std::cout << token_name << " pop\n";

        if (actual_token.get_attribute("action") == "gvardef"){
            define_variable(token_name);
        } 
        else if (actual_token.get_attribute("action") == "varset"){
            push_called_token();
        } 
        else if (actual_token.get_attribute("action") == "gfundef"){
            define_function(token_name);
        }
        else if (actual_token.get_attribute("action") == "function"){
            call_function(token_name);
        }
        else if (actual_token.get_attribute("action") == "return"){
            push_called_token();
        }
        if (actual_token.get_attribute("operator") != ""){ 
            push_called_token();
        }
        else if (actual_token.get_attribute("type") == "cst") {
            w_push_cst(std::stoi(actual_token.get_attribute("value")));
            pop_called_token();
        }
        else if (actual_token.get_attribute("type") == "var")
        {
            w_get_var(functions[called_fun_names.back()].vars[token_name].offset);
            pop_called_token();
        }
        else if (actual_token.get_attribute("type") == "parenthesis"){
            push_children(true);
        }
    }
    end();
}