#include "gstmt.hpp"
#include "stmt.hpp"
#include "expr.hpp"

void GStmt::print(string indent){
    v_cout << indent << "GStmt: " << "\n";
}

void GFunDef::print(string indent){
    v_cout << indent << "GFunDef: " << type << " " << name << "\n";
    // for(auto v : args){
    //     v->print(indent + "  ");
    // }
    body->print(indent + "  ");
}

void GVarDef::print(string indent){
    v_cout << indent << "GVarDef: " << type << " " << name << "\n";
    if(value != nullptr){
        value->print(indent + "  ");
    }
}
