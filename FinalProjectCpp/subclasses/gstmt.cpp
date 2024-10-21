#include "gstmt.hpp"
#include "stmt.hpp"
#include "expr.hpp"

void GStmt::print(string indent){
    std::cout << indent << "GStmt: " << "\n";
}

void GFunDef::print(string indent){
    std::cout << indent << "GFunDef: " << type << " " << name << "\n";
    // for(auto v : args){
    //     v->print(indent + "  ");
    // }
    body->print(indent + "  ");
}

void GVarDef::print(string indent){
    std::cout << indent << "GVarDef: " << type << " " << name << "\n";
    if(value != nullptr){
        value->print(indent + "  ");
    }
}
