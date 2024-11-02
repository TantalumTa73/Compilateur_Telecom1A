#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

void w_call_function(string str){
    if (str == PRINT_INT){
        add_line("call print_int");
        add_line();
    } else if (str == PRINTF){
        add_line("calling printf",true,true);
        // add_line("call printf");
        add_line();
    } else {
        add_line("calling function as expr", true, true);
        add_line("call " + str);
        add_line("add $" + std::to_string(SIZE_INT) + ", %rsp");
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
}

void w_call_read(string str, int val, bool is_global){
    add_line("read value", true, true);
    add_line("call scan");
    if (is_global){
    add_line("mov %rax, $" + std::to_string(val) + "(%rbp)");
    } else {
    add_line("mov %rax, $" + std::to_string(val) + "(%rip)");
    }
    add_line();
}
