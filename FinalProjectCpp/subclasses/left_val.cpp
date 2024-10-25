#include "left_val.hpp"
#include "expr.hpp"

void LeftValue::print(string indent){
    v_cout << indent << "LeftValue" << endl;
}

void VarGet::print(string indent){
    v_cout << indent << "VarGet : " << name << endl;
}

void ArrayGet::print(string indent){
    v_cout << indent << "ArrayGet" << endl;
    left_value->print(indent + "  ");
    index->print(indent + "  ");
}