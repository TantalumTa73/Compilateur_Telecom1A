#include "expr.hpp"
#include "litteral.hpp"
#include "left_val.hpp"

void Expr::print(string indent){
    v_cout << indent << "Expr" << endl;
}

void ValueGet::print(string indent){
    v_cout << indent << "ValueGet" << endl;
    value->print(indent + "  ");
}

void List::print(string indent){
    v_cout << indent << "List" << endl;
    for(auto v : values){
        v->print(indent + "  ");
    }
}

void FunCall::print(string indent){
    v_cout << indent << "FunCall" << endl;
    v_cout << indent + "  " << name << endl;
    for(auto v : args){
        v->print(indent + "  ");
    }
}

void LRop::print(string indent){
    v_cout << indent << "LRop : " << op << endl;
    left_value->print(indent + "  ");
}

void Uniop::print(string indent){
    v_cout << indent << "Uniop : " << uniop << endl;
    value->print(indent + "  ");
}

void Binop::print(string indent){
    v_cout << indent << "Binop : " << binop << endl;
    v1->print(indent + "  ");
    v2->print(indent + "  ");
}

void Ternop::print(string indent){
    v_cout << indent << "Ternop" << endl;
    condition->print(indent + "  ");
    v_cout << indent + "  ?" << endl;
    v1->print(indent + "  ");
    v_cout << indent + "  :" << endl;
    v2->print(indent + "  ");
}

