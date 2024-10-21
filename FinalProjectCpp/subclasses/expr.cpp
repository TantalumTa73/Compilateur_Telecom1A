#include "expr.hpp"
#include "litteral.hpp"
#include "left_val.hpp"

void Expr::print(string indent){
    cout << indent << "Expr" << endl;
}

void Const::print(string indent){
    cout << indent << "Const" << endl;
    value->print(indent + "  ");
}

void VarGet::print(string indent){
    cout << indent << "VarGet" << endl;
    value->print(indent + "  ");
}

void List::print(string indent){
    cout << indent << "List" << endl;
    for(auto v : values){
        v->print(indent + "  ");
    }
}

void FunCall::print(string indent){
    cout << indent << "FunCall" << endl;
    cout << indent + "  " << name << endl;
    for(auto v : args){
        v->print(indent + "  ");
    }
}

void LeftValOp::print(string indent){
    cout << indent << "LeftValOp" << endl;
    left_value->print(indent + "  ");
    cout << indent + "  " << op << endl;
}

void Uniop::print(string indent){
    cout << indent << "Uniop : " << uniop << endl;
    value->print(indent + "  ");
}

void Binop::print(string indent){
    cout << indent << "Binop" << endl;
    v1->print(indent + "  ");
    cout << indent + "  " << binop << endl;
    v2->print(indent + "  ");
}

void Ternop::print(string indent){
    cout << indent << "Ternop" << endl;
    condition->print(indent + "  ");
    cout << indent + "  ?" << endl;
    v1->print(indent + "  ");
    cout << indent + "  :" << endl;
    v2->print(indent + "  ");
}

