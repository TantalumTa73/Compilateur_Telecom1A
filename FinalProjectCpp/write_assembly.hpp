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
void w_init_var(int size, int address = 0);
void w_init_global_var(string str, int size);
// void w_set_var(string add, string op);
void w_set_var(string op);
// void w_get_var(int val);

// push.cpp
void w_push_cst(int val);
// void w_push_var(string str);
void w_push_var();
void w_push_add(string str);

// functions.cpp
void w_init_f(string str);
void w_call_function(string str, int args);
void w_call_read(int val, bool is_global);

// operators.cpp
void def_operators();
void w_uniop(string op_name);
void w_binop(string op_name);
void w_ternop();
void w_lrop(string op);
void w_llop(string op);
void w_rlop(string op);
void w_array_get();
void w_array_get2(int size);

// end.cpp
void w_ret(bool main, bool has_arg = true);
// void 
void end();
