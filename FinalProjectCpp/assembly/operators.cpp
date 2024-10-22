#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

void def_operators(){
    operators["plus"] = "add %rax, %rbx\n";
    operators["minus"] = "sub %rbx, %rax\n\tmov %rax, %rbx\n";
    operators["mult"] = "imul %rax, %rbx\n";
    operators["division"] = "cqo\n\tidivq %rbx\n\tmov %rax, %rbx\n";
    operators["modulo"] = "xor %rdx, %rdx\nidivq %rbx\nmov %rdx, %rbx\n";
    operators["uminus"] = "pop %rax\n\tneg %rax\n\tpush %rax\n";

    // | Add -> "+"
    // | Sub -> "-"
    // | Mul -> "*"
    // | Div -> "/"
    // | Mod -> "%"
    // | Leq -> "<="
    // | Le -> "<"
    // | Geq -> ">="
    // | Ge -> ">"
    // | Neq -> "!="
    // | IsEq -> "=="
    // | And -> "&&"
    // | Or -> "||"
    // | Xor -> "^"
    // | Lshift -> "<<"
    // | Rshift -> ">>"
    // | BAnd -> "&"
    // | BOr -> "|"


    // | Neg -> "-"
    // | Not -> "!"
    // | Inv -> "~"
    // | Dereference -> "*x"

//       | POSTINCR -> "x++"
//   | POSTDECR -> "x--"
//   | PREINCR -> "++x"
//   | PREDECR -> "--x"
//   | GetAdress -> "&x"

//   | Eq -> "="
//   | AddEq -> "+="
//   | SubEq -> "-="
//   | MulEq -> "*="
//   | DivEq -> "/="
//   | ModEq -> "%="
}


void w_op(string op_name){
    add_line(op_name + " operation", true, true);
    add_line("pop %rbx");
    add_line("pop %rax");
    if (auto search = operators.find(op_name); search == operators.end()){
        v_cout << op_name << " unknown in operators";
        throw invalid_argument(op_name+" unknown operator");
    }
    add_line(operators[op_name]);
    add_line("push %rbx");
    add_line();
}