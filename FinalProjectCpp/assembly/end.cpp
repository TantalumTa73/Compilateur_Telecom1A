#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

void w_ret(bool is_main, bool has_arg){
    add_line("return ", true, true);
    if (is_main) add_line("xor %rax, %rax");
    else if (has_arg) add_line("pop %rax");
    
    add_line("mov %rbp, %rsp");
    add_line("pop %rbp");
    add_line("ret");
    add_line();
}


void end(){
    add_line(".section .note.GNU-stack\n\t");
    file.close();
}
