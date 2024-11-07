#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"
#include "../context.hpp"

extern unordered_map<string, Context> contexts ;
extern vector<string> called_contexts ;
extern vector<tuple<string, string>> local_string ;
extern vector<tuple<string, Tk>> global_var_init ;

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

    // v_cout << "end\nlocal_string :   ";
    add_line();
    set_section("data");
    for (auto [name, value] : local_string){
        add_line(name + ":", false);
        add_line(".asciz \"" + value + "\"");
    }

    v_cout << "global_var_init :   ";
    for (auto [name, value] : global_var_init){
        v_cout << name << " : " << value->tk_type << " ; ";
    }
    v_cout << "\n";

    add_line();
    add_line(".section .note.GNU-stack");
    add_line();
    file.close();
}
