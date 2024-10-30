#include "assembly.hpp"

void Jz::print(string indent){
    v_cout << indent << "Jz: " << label << "\n";
}

void Jmp::print(string indent){
    v_cout << indent << "Jmp: " << label << "\n";
}

void Label::print(string indent){
    v_cout << indent << "Label: " << label << "\n";
}