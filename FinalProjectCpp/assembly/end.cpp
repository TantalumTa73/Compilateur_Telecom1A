#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

void w_ret(bool main){
    add_line("return", true, true);
    // if (main) {
    //     add_line("xor %rax, %rax");
    //     add_line("ret");
    //     add_line();
    //     return;
    // }
    add_line("pop %rax");
    add_line("");
    add_line("mov %rbp, %rsp");
    add_line("pop %rbp");
    add_line("ret");
    add_line();
}


void end(){
    file.close();
}
