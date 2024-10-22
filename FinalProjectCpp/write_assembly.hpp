#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

#include "define.hpp"

extern string current_section_w;
extern unordered_map<string, string> unary_operators;
extern unordered_map<string, string> binary_operators;
extern unordered_map<string, string> left_val_operators;
extern unordered_map<string, string> assign_operators;
extern ofstream file;

// init.cpp
void init();
void w_init_template();

// other.cpp
void add_line(string str = "", bool indent = true, bool comment = false);
void set_section(string str);
void w_print(string str);

// variables.cpp
void w_init_var();
void w_init_global_var(string str);
void w_set_var(int val);
void w_set_global_var(string str);
void w_get_var(int val);

// push.cpp
void w_push_cst(int val);
void w_push_local_var(int val);
void w_push_global_var(string str);

// functions.cpp
void w_init_f(string str); // init a function
void w_call_function(string str);
void w_call_read(string str, int val, bool is_global);

// operators.cpp
void def_operators();
void w_uniop(string op_name);
void w_binop(string op_name);
void w_ternop();
void w_left_val_op(string op_name);

// end.cpp
void w_ret(bool main);
void end();
