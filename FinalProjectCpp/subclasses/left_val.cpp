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

void LLop::print(string indent){
    v_cout << indent << "LLop : " << op << endl;
    left_value->print(indent + "  ");
}

void RLop::print(string indent){
    v_cout << indent << "RLop : " << op << endl;
    value->print(indent + "  ");
}