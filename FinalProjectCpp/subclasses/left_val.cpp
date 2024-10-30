#include "left_val.hpp"
#include "expr.hpp"
#include "litteral.hpp"

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

/*
string VarGet::get_address(int shift) {
    // Variable variable = find_var(name);
    // return variable.get_adress(shift);
    w_push_add(name);
}
string ArrayGet::get_address(int shift) {
    // if (index->tk_type == LITTERAL_INT) {
    //     int i = ((Int*)index)->value * SIZE_INT;
    //     return left_value->get_address(shift-i);
    // }
    // ERROR("ArrayGet not implemented");
    
    w_array_get();
}
string LLop::get_address(int shift) {
    // if (op == "++x" || op == "--x") {
    //     return left_value->get_address() ;
    // } else {
    //     ERROR("LLop " + op +" is not implemented");
    // }
}
string RLop::get_address(int shift) {
    // operator *x
    
    // w_push_var(value->get_address(shift));
    

    // return "";
}
*/