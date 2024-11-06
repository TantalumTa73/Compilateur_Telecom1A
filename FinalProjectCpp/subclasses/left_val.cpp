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



int VarGet::get_size_obj(int level) {

    Variable var = find_var(name);
    
    uint len = level ;

    v_cout << "Var get size " << name << " " << level << " : " ;
    for (int i : var.array_size) v_cout << i << " ";
    v_cout << endl;

    if ( len >= var.array_size.size()) {
        ERROR("Error in VarGet : array size out of range " + to_string(len));
    }
    return var.array_size[level];
}