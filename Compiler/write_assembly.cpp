#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "write_assembly.hpp"
#include "data.hpp"

std::string current_section_w;
std::unordered_map<std::string, std::string> operators;
std::ofstream file;

void init(std::string str){
    file.open(str, std::ios::out);

    operators["plus"] = "add %rax, %rbx\n";
    operators["minus"] = "sub %rbx, %rax\n\tmove %rax, %rbx\n";
    operators["mult"] = "imul %rax, %rbx\n";
    operators["division"] = "cqo\n\tidivq %rbx\n\tmov %rax, %rbx\n";
    operators["modulo"] = "xor %rdx, %rdx\nidivq %rbx\nmov %rdx, %rbx\n";
    operators["uminus"] = "pop %rax\n\tneg %rax\n\tpush %rax\n";
    
    w_init_template();
}

void add_line(std::string str = "", bool indent = true, bool comment = false){
    if (indent){
        file << "\t";
    }
    if (comment){
        file << COMMENT;
    }
    file << str << "\n";
}

void set_section(std::string str){
    add_line();
    if (str != current_section_w) {
        add_line(".section ." + str, false);
        add_line();
        current_section_w = str;
    }
}

void w_init_template(){
   std::ifstream src("Compiler/template.s");
   std::string line;
   while (getline(src, line)) {
        add_line(line, false, false);
   }
   src.close();
}

void w_init_f(std::string str){
    add_line("init function " + str, true, true);
    set_section("text");
    add_line(str + ":", false);
    add_line("push %rbp");
    add_line("mov %rsp, %rbp");
    add_line();
}

void w_ret(bool main){
    add_line("return", true, true);
    if (main) {
        add_line("xor %rax, %rax");
        add_line("ret");
        add_line();
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

void w_push_cst(int val){
    add_line("push cst", true, true);
    add_line("push $" + std::to_string(val));
    add_line();
}

void w_call_read(std::string str, int val, bool is_global){
    add_line("read value", true, true);
    add_line("call scan");
    if (is_global){
    add_line("mov %rax, $" + std::to_string(val) + "(%rbp)");
    } else {
    add_line("mov %rax, $" + std::to_string(val) + "(%rip)");
    }
    add_line();
}

void w_call_function(std::string str){
    if (str == PRINT){
        add_line("call print");
        add_line();
    } else {
        add_line("calling function as expr", true, true);
        add_line("call " + str);
        add_line("add $" + std::to_string(SIZE) + ", %rsp");
        add_line("push %rax");
        add_line();
    }
}

void w_print(std::string str){
}

void w_op(std::string op_name){
    add_line(operators[op_name]);
    add_line();
}

void end(){
    file.close();
}
