#include <string>
#include "write_assembly.hpp"

void w_init_s(){
    file << "       section .text\n";
    file << "       .globl main\n";
    file << "\n";
}

void w_init_f(std::string str){
    file << str << ":\n";
}

void w_ret(){
    file << "       ret\n";
}

void w_init_var(std::string str){
    file << "       pushq $" << str << "\n";
}

void w_alloc(int space){
    file << "       subq $" << space << "\n";
}

void w_set_var(std::string str, int val){
    file << 
}

void w_print(std::string str){
    file << "\n"; 
    file << "\n"; 
    file << "\n"; 
}

void w_arithm(std::string str, std::string op, int x, int y) {}
