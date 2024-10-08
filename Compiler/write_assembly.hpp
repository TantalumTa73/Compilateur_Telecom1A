#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include "../Interpreter/token.hpp"

std::unordered_map<std::string, std::string> operators;

void w_init_template();
void w_init_f(std::string str); // init a function
void w_print(std::string str);
void w_init_var();
void w_init_global_var(std::string str);
void w_set_var(std::string str, int val);
void w_get_var(std::string str);
void w_push_cst(int val);
void w_op(std::string op_name);