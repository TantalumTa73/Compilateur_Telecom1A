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