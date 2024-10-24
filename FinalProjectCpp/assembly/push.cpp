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

// void w_push_local_var(int val){
//     add_line("push local variable", true, true);
//     add_line("push " + std::to_string(val) + "(%rbp)");
//     add_line();
// }

// void w_push_global_var(string str){
//     add_line("push global variable", true, true);
//     add_line("push " + str + "(%rip)");
//     add_line();
// }
void w_push_var(string add){
    add_line("push variable", true, true);
    add_line("push " + add);
    add_line();
}
