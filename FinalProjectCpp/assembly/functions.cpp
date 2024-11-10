#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

void w_call_printf(int args){
    if (args == 0) ERROR("call fun : printf without args");
    else if (args == 1){
        // lea s1(%rip), %rax
        // mov %rax, %rdi
        add_line("pop %rax");
        add_line("mov %rax, %rdi");
        add_line("movb $0, %al");
        add_line("call printf");
        add_line();
    } else if (args == 2){
        add_line("pop %rax");
        add_line("mov %rax, %rdi");
        add_line("pop %rsi");
        add_line("movb $0, %al");
        add_line("call printf");
        add_line();
    } else if (args == 3){
        add_line("pop %rax");
        add_line("mov %rax, %rdi");
        add_line("pop %rsi");
        add_line("pop %rdx");
        add_line("movb $0, %al");
        add_line("call printf");
        add_line();
    } else {
        ERROR("call fun : printf with too many args");
    }
    
}

void w_call_scanf(int args){
    if (args == 0) ERROR("scanf : no args");
    else if (args == 1){
        ERROR("scanf : only one arg, should get 2");
    } else if (args == 2){
        add_line("pop %rdi");
        add_line("pop %rsi");
        add_line("movb $0, %al");
        add_line("sub $8, %rsp ");
        add_line("call scanf");
        add_line();

    } else if (args == 3){
        // add_line("pop %rax");
        // add_line("mov %rax, %rdi");
        // add_line("pop %rsi");
        // add_line("pop %rdx");
        // add_line("movb $0, %al");
        // add_line("call scanf");
        // add_line();
        ERROR("scanf : too many args");
    } else {
        ERROR("scanf : too many args");
    }
}


void w_call_function(string str, int args){
    
    if (str == PRINT_INT){
        add_line("call print_int");
        add_line();
    } else if (str == PRINT_CHAR){
        add_line("calling print_char", true, true);
        add_line("pop %rax");
        add_line("movsbl %al, %edi"); // convert char to int
        add_line("call putchar");
        add_line("mov $10, %rdi");
        add_line("call putchar"); // print newline
        add_line();
    } else if (str == PRINTF){
        w_call_printf(args);
    } else if (str == SCANF){
        w_call_scanf(args);
    } else if (str == MALLOC){
        add_line("calling malloc",true,true);
        add_line("pop %rdi");
        add_line("call malloc");
        add_line("push %rax");
        add_line();
        // movq    add, %rax
        // movq    val, (%rax)
        // ERROR("malloc not yet implemented");
    } else {
        add_line("calling function as expr", true, true);
        add_line("call " + str);
        // add_line("add $" + std::to_string(SIZE_INT) + ", %rsp");
        for (int i = 0; i < args; i++) add_line("pop %rcx");
        add_line("push %rax");
        add_line();
    }
}

void w_init_f(string str){
    set_section("text");
    add_line(str + ":", false);
    add_line("push %rbp");
    add_line("mov %rsp, %rbp");
    add_line();

    if (str != MAIN) return ;

    add_line("main function", true, true);
    add_line();
}

void w_call_read(int val, bool is_global){
    add_line("read value", true, true);
    add_line("call scan");
    if (is_global){
    add_line("mov %rax, $" + std::to_string(val) + "(%rbp)");
    } else {
    add_line("mov %rax, $" + std::to_string(val) + "(%rip)");
    }
    add_line();
}
