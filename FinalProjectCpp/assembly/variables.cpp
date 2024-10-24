#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"


void w_init_var(){
    add_line("init local variable", true, true);
    add_line("sub $" + std::to_string(SIZE) + ", %rsp");
    add_line();
}

void w_init_global_var(string str){
    add_line("init global variable", true, true);
    // add_line("pop " + str + "(%rip)");
    set_section("bss");
    add_line(".align " + std::to_string(SIZE));
    add_line(".type " + str + ", @object");
    add_line(".size " + str + ", " + std::to_string(SIZE));
    add_line(str + ":", false);
    add_line(".zero " + std::to_string(SIZE));
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
    } else throw invalid_argument("op " + op + " is not implemented");
    add_line();
}

void w_get_var(int val){
    add_line("get variable", true, true);
    add_line("push " + std::to_string(val) + "(%rbp)");
    add_line();
}
// .section .note.GNU-stack\n\t