#include <string>
#include <fstream>
#include <vector>

#include "write_assembly.hpp"
#include "data.hpp"
#include "../Interpreter/token.hpp"

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

void w_ret(){
    add_line("ret");
}

void w_init_var(){
    add_line("subq $" + std::to_string(SIZE) + ", %rsp");
}

void w_init_global_var(std::string str, int val){
    set_section("bss");
    add_line(".align " + std::to_string(SIZE));
    add_line(".type" + str + ", @object");
    add_line(".size " + str + ", " + std::to_string(SIZE));
    add_line(str + ":", false);
    add_line(".zero " + std::to_string(SIZE));
        
}

void w_set_var(std::string str, int val, int offset){

}

void w_get_var(std::string str){

}

void w_push_cst(int val){
    add_line("pushq $" + std::to_string(val));
}

void w_print(std::string str){
}

void w_op(std::string op_name){
    operators["plus"] = "add %rax, %rbx";
    operators["minus"] = "sub %rbx, %rax\n\tmove %rax, %rbx";
    operators["mult"] = "imul %rax, %rbx";
    operators["division"] = "cqo\n\tidivq %rbx\n\tmov %rax, %rbx";
    operators["modulo"] = "xor %rdx, %rdx\nidivq %rbx\nmov %rdx, %rbx";

    }

}
