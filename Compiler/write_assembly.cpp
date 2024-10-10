#include <string>
#include <fstream>
#include <vector>

#include "write_assembly.hpp"
#include "data.hpp"

void add_line(std::string str = "", bool indent = true, bool comment = false){
    if (indent)
        file << "\t";
    if (comment)
        file << COMMENT;
    file << str << "\n";
}

void set_section(std::string str){
    add_line();
    if (str != current_section) {
        add_line("." + str);
        current_section = str;
    }
}

void w_init_template(){
   std::ifstream src("template.s", std::ios::binary);
   file << src.rdbuf();
   src.close();
}

void w_init_f(std::string str){
    set_section("text");
    add_line(str + ":", false);
    add_line("push %rbp");
    add_line("mov %rsp, %rbp");
}

void w_ret(bool main){
    if (main) {
        add_line("xor %rax, %rax");
        add_line("ret");
        return;
    }
    add_line("pop %rax");
    add_line("");
    add_line("mov %rbp, %rsp");
    add_line("pop %rbp");
    add_line("ret");
    add_line();
}

void w_init_var(){
    add_line("sub $" + std::to_string(SIZE) + ", %rsp");
}

void w_init_global_var(std::string str, int val){
    set_section("bss");
    add_line(".align " + std::to_string(SIZE));
    add_line(".type" + str + ", @object");
    add_line(".size " + str + ", " + std::to_string(SIZE));
    add_line(str + ":", false);
    add_line(".zero " + std::to_string(SIZE));
        
}

void w_set_var(int val){
    add_line("pop " + std::to_string(val) + "(%rbp)");
}

void w_set_global_var(std::string str){
        add_line("pop %rax");
        add_line("mov %rax, " + str + "(%rip)");
        add_line();
}

void w_get_var(int val){
    add_line("push $" + std::to_string(val) + "(%rbp)");
}

void w_push_cst(int val){
    add_line("push $" + std::to_string(val));
}

void w_call_function(std::string str){
    add_line("calling function as expr", true, true);
    add_line("call " + str);
    add_line("add $" + std::to_string(SIZE) + ", %rsp");
    add_line("push %rax");
    add_line();
}

void w_print(std::string str){
}

void w_op(std::string op_name){
    add_line(operators[op_name]);
}
