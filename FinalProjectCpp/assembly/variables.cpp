#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "write_assembly.hpp"


void w_init_var(){
    add_line("init local variable", true, true);
    add_line("sub $" + std::to_string(SIZE) + ", %rsp");
    add_line();
}

void w_init_global_var(std::string str){
    add_line("init global variable", true, true);
    set_section("bss");
    add_line(".align " + std::to_string(SIZE));
    add_line(".type " + str + ", @object");
    add_line(".size " + str + ", " + std::to_string(SIZE));
    add_line(str + ":", false);
    add_line(".zero " + std::to_string(SIZE));
    add_line();
        
}

void w_set_var(int val){
    add_line("set local variable", true, true);
    add_line("pop %rax");
    add_line("mov %rax, " + std::to_string(val) + "(%rbp)");
    add_line();
}

void w_set_global_var(std::string str){
    add_line("set global variable", true, true);
        add_line("pop %rax");
        add_line("mov %rax, " + str + "(%rip)");
        add_line();
}

void w_get_var(int val){
    add_line("get variable", true, true);
    add_line("push " + std::to_string(val) + "(%rbp)");
    add_line();
}
