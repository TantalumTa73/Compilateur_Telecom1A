#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

unordered_map<string, string> unary_operators;
unordered_map<string, string> binary_operators;
unordered_map<string, string> left_val_operators;
unordered_map<string, string> assign_operators;

inline void def_uniop(){
    
    unary_operators["-"] = "neg %rax\n";
    unary_operators["!"] = "cmp $0, %rax\n\tsete %al\n\tmovzbq %al, %rax\n";
    unary_operators["~"] = "not %rax\n";
    unary_operators["*x"] = "mov (%rax), %rax\n";
    // unary_operators["&"] = "";
}

inline void def_binop(){
    binary_operators["+"] = "add %rax, %rbx\n";
    binary_operators["-"] = "sub %rbx, %rax\n\tmov %rax, %rbx\n";
    binary_operators["*"] = "imul %rax, %rbx\n";
    binary_operators["/"] = "cqo\n\tidivq %rbx\n\tmov %rax, %rbx\n";
    binary_operators["%"] = "xor %rdx, %rdx\n\tidivq %rbx\n\tmov %rdx, %rbx\n";

    // binary_operators["<="] = "\n";
    // binary_operators["<"] = "\n";
    // binary_operators[">="] = "\n";
    // binary_operators[">"] = "\n";
    // binary_operators["!="] = "\n";
    // binary_operators["=="] = "\n";
    // test + cmov ?

    // binary_operators["&&"] = "\n"; // NEED TO BE LAZY
    // binary_operators["||"] = "\n"; // NEED TO BE LAZY

    binary_operators["<<"] = "mov %rbx, %rcx\n\tsal %cl, %rax\n\tmov %rax, %rbx";
    binary_operators[">>"] = "mov %rbx, %rcx\n\tsar %cl, %rax\n\tmov %rax, %rbx";
    
    binary_operators["&"] = "and %rax, %rbx\n";
    binary_operators["|"] = "or %rax, %rbx\n";
    binary_operators["^"] = "xor %rax, %rbx\n";
}

inline void def_leftvalop(){
    // left_val_operators["x++"] = "" ;
    // left_val_operators["x--"] = "" ;
    // left_val_operators["++x"] = "" ;
    // left_val_operators["--x"] = "" ;
    // left_val_operators["&x"] = "" ;

    // add = x(%rip) or -8(%rbp)
	// mov x(%rip),%rax
    // mov %rax, %rbx
	// add $1, %rbx
	// mov %rbx, x(%rip)
}



void def_operators(){
    def_uniop();
    def_binop();
    def_leftvalop();
}


void w_uniop(string op_name){
    add_line("uniop: "+op_name, true, true);
    add_line("pop %rax");
    if (auto search = unary_operators.find(op_name); 
        search == unary_operators.end())
        throw invalid_argument(op_name+" unknown unary_operators");
    
    add_line(unary_operators[op_name]);
    add_line("push %rax");
    add_line();
}

void w_binop(string op_name){
    add_line("binop "+op_name, true, true);
    add_line("pop %rbx");
    add_line("pop %rax");
    if (auto search = binary_operators.find(op_name); 
        search == binary_operators.end())
        throw invalid_argument(op_name+" unknown binary_operators");
    
    add_line(binary_operators[op_name]);
    add_line("push %rbx");
    add_line();
}

void w_ternop(){
    add_line("ternop", true, true);
    add_line("pop %rcx");
    add_line("pop %rbx");
    add_line("pop %rax");

    add_line("test %rax, %rax");
    add_line("cmovz %rbx, %rcx");
    add_line("push %rcx");

    add_line();
}

void w_left_val_op(string op, string add){
    add_line("left_val_op "+op, true, true);

    if        (op == "++x") {
        add_line("mov "+add+", %rax");
        add_line("inc %rax");
        add_line("mov %rax, "+add);
        add_line("push %rax");
    } else if (op == "x++") {
        add_line("mov "+add+", %rax");
        add_line("push %rax");
        add_line("inc %rax");
        add_line("mov %rax, "+add);
    } else if (op == "--x") {
        add_line("mov "+add+", %rax");
        add_line("dec %rax");
        add_line("mov %rax, "+add);
        add_line("push %rax");
    } else if (op == "x--") {
        add_line("mov "+add+", %rax");
        add_line("push %rax");
        add_line("dec %rax");
        add_line("mov %rax, "+add);
    } else if (op == "&x") {
        add_line("lea "+add+", %rax");
        add_line("push %rax");
    } else throw invalid_argument("left_val_op " + op + " is not implemented");

    add_line();

}

void w_assign_op(string op_name){
    add_line("assign_op "+op_name, true, true);
    add_line("pop %rbx");
    add_line("pop %rax");
    if (auto search = assign_operators.find(op_name); 
        search == assign_operators.end())
        throw invalid_argument(op_name+" unknown assign_operators");
    
    add_line(assign_operators[op_name]);
    add_line("push %rbx");
    add_line();
}

