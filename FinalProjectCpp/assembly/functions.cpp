#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

void w_call_function(string str, int args){
    if (str == PRINT_INT){
        add_line("call print_int");
        add_line();
    } else if (str == PRINT_CHAR){
        add_line("calling print_char", true, true);
        add_line("pop %rdi");
        add_line("call putchar");
        add_line("mov $10, %rdi");
        add_line("call putchar");
        add_line();
    } else if (str == PRINTF){
        add_line("calling printf",true,true);
        // add_line("call printf");
        add_line();
    } else {
        add_line("calling function as expr", true, true);
        add_line("call " + str);
        // add_line("add $" + std::to_string(SIZE_INT) + ", %rsp");
        for (int i = 0; i < args; i++) add_line("pop %rcx");
        add_line("push %rax");
        add_line();
    }
}

void w_init_f(string str){
    set_section("text");
    add_line(str + ":", false);
    add_line("push %rbp");
    add_line("mov %rsp, %rbp");
    add_line();

    if (str != MAIN) return ;

    add_line("main function", true, true);
    add_line();
}

void w_call_read(int val, bool is_global){
    add_line("read value", true, true);
    add_line("call scan");
    if (is_global){
    add_line("mov %rax, $" + std::to_string(val) + "(%rbp)");
    } else {
    add_line("mov %rax, $" + std::to_string(val) + "(%rip)");
    }
    add_line();
}
