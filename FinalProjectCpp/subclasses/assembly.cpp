#include "assembly.hpp"

void CmdX86::print(string indent){
    v_cout << indent << "CmdX86: " << cmd << "\n";
}

void Jz::print(string indent){
    v_cout << indent << "Jz: " << label << "\n";
}
void Jnz::print(string indent){
    v_cout << indent << "Jnz: " << label << "\n";
}
void Jmp::print(string indent){
    v_cout << indent << "Jmp: " << label << "\n";
}

void Label::print(string indent){
    v_cout << indent << "Label: " << label << "\n";
}