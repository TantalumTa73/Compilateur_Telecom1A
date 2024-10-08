#pragma once

#include <string>
#include <fstream>

std::ofstream file;

void w_init_s(); // init the .s file
void w_init_f(std::string str); // init a function
void w_alloc(int space); // allocate space bit on the stack
void w_print(std::string str);
void w_init_var(std::string str);
void w_set_var(std::string str, int value);
void w_arithm(std::string str, std::string opp, int x, int y);