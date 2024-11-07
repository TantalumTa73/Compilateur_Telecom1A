#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"


void w_push_cst(int val){
    add_line("push cst", true, true);
    add_line("push $" + std::to_string(val));
    add_line();
}


void w_push_var(string add){
    add_line("push variable", true, true);
    add_line("push " + add);
    add_line();
}

void w_push_var(){
    add_line("push value from address", true, true);
    add_line("pop %rax");
    add_line("push (%rax)");
    add_line();
}

void w_push_add(string add){
    add_line("push address", true, true);
    add_line("lea "+add+", %rbx");
    add_line("push %rbx");
    add_line();
}

void w_convert_to_bool(){
    add_line("convert to bool", true, true);
    add_line("pop %rax");
    add_line("cmp $0, %rax");
    add_line("jnz nothing");
    add_line();
    add_line("push $1");
    add_line();
    add_line("nothing:", false);
    add_line();
}