#include "left_val.hpp"
#include "expr.hpp"

void LeftValue::print(string indent){
    v_cout << indent << "LeftValue" << endl;
}

void Var::print(string indent){
    v_cout << indent << "Var : " << name << endl;
}

void Array::print(string indent){
    v_cout << indent << "Array" << endl;
    left_value->print(indent + "  ");
    index->print(indent + "  ");
}