#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"


void w_init_var(int size, int address){
    add_line("init local variable", true, true);
    if (address != 0) {
        // add_line("pop %rax");
        add_line("pop " + std::to_string(address) + "(%rbp)");
    }
    add_line("sub $" + std::to_string(size) + ", %rsp");
    add_line();
    // push -8(%rbp)
    // sub $8, %rsp
}

void w_init_global_var(string str){
    add_line("init global variable", true, true);
    // add_line("pop " + str + "(%rip)");
    set_section("bss");
    add_line(".align " + std::to_string(SIZE_INT));
    add_line(".type " + str + ", @object");
    add_line(".size " + str + ", " + std::to_string(SIZE_INT));
    add_line(str + ":", false);
    add_line(".zero " + std::to_string(SIZE_INT));
    add_line();
        
}

void w_set_var(string add, string op){
    // set local or global variable with the last value in the stack

    add_line("set local variable : "+op, true, true);
    if        (op == "=") {
        add_line("pop " + add);
    } else if (op == "+=") {
        add_line("pop %rax");
        add_line("add %rax, " + add);
    } else if (op == "*=") {
        add_line("pop %rax");
        add_line("mov "+add + ", %rbx");
        add_line("imul %rax, %rbx");
        add_line("mov %rbx, " + add);
    } else if (op == "/=") {
        add_line("pop %rbx");
        add_line("mov " + add +", %rax");
        add_line("xor %rdx, %rdx");
        add_line("idivq %rbx");
        add_line("mov %rax, "+add);
    } else if (op == "%=") {
        add_line("pop %rbx");
        add_line("mov "+add+", %rax");
        add_line("xor %rdx, %rdx");
        add_line("idivq %rbx");
        add_line("mov %rdx, "+add);
    } else ERROR("op " + op + " is not implemented");
    add_line();
}

void w_set_var(string op){
    // set local or global variable with the last value in the stack

    add_line("set local variable : "+op, true, true);
    if        (op == "=") {
        add_line("pop %rbx");
        add_line("pop %rax");
        add_line("mov %rbx, (%rax)");

    } else if (op == "+=") {
        add_line("pop %rbx");
        add_line("pop %rax");
        add_line("add %rbx, (%rax)");
    } else if (op == "-=") {
        add_line("pop %rbx");
        add_line("pop %rax");
        add_line("sub %rbx, (%rax)");
    } else if (op == "*=") {
        add_line("pop %rbx");
        add_line("pop %rax");
        add_line("imul (%rax), %rbx");
        add_line("mov %rbx, (%rax)");
    } else if (op == "/=") {
        add_line("pop %rbx");
        add_line("pop %rcx");
        add_line("mov (%rcx), %rax");
        add_line("cqo");
        add_line("idiv %rbx");
        add_line("mov %rax, (%rcx)");
    } else if (op == "%=") {
        add_line("pop %rbx");
        add_line("pop %rcx");
        add_line("mov (%rcx), %rax");
        add_line("cqo");
        add_line("idiv %rbx");
        add_line("mov %rdx, (%rcx)");
    } else ERROR("op " + op + " is not implemented");
    add_line();
}

// void w_get_var(int val){
//     add_line("get variable", true, true);
//     add_line("push " + std::to_string(val) + "(%rbp)");
//     add_line();
// }
