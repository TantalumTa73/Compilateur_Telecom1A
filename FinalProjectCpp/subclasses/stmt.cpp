#include "stmt.hpp"
#include "expr.hpp"
#include "left_val.hpp"

void Stmt::print(string indent){
    v_cout << indent << "Stmt" << endl;
}

void Sscope::print(string indent){
    v_cout << indent << "Sscope (" << name << ")\n";
    for(auto v : body){
        v->print(indent + "  ");
    }
}

void Sreturn::print(string indent){
    v_cout << indent << "Sreturn" << endl;
    if (value != nullptr) value->print(indent + "  ");
}

void Skeyword::print(string indent){
    v_cout << indent << "Skeyword: " << keyword << endl;
}

void Sfor::print(string indent){
    v_cout << indent << "Sfor" << endl;
    init->print(indent + "  ");
    condition->print(indent + "  ");
    update->print(indent + "  ");
    body[0]->print(indent + "  ");
}

void Swhile::print(string indent){
    v_cout << indent << "Swhile" << endl;
    condition->print(indent + "  ");
    body[0]->print(indent + "  ");
}

void SvarDef::print(string indent){
    v_cout << indent << "SvarDef: " << type << " " << name ;
    for (auto i : ladder) v_cout << "[" << i << "]";
    v_cout << endl;
    if(value != nullptr){
        value->print(indent + "  ");
    }
}

void SvarSet::print(string indent){
    v_cout << indent << "SvarSet" << endl;
    left_value->print(indent + "  ");
    v_cout << indent + "  " << op << endl;
    value->print(indent + "  ");
}

void Sexpr::print(string indent){
    v_cout << indent << "Sexpr" << endl;
    value->print(indent + "  ");
}

void Sif::print(string indent){
    v_cout << indent << "Sif ( " ;
    v_cout << label_endif->label << " )" << endl;
    condition->print(indent + "  ");
    body->print(indent + "  ");
}

void SifElse::print(string indent){
    v_cout << indent << "SifElse ( " << label_else->label << ",  " ;
    v_cout << label_endif->label << " )" << endl;
    condition->print(indent + "  ");
    body_if->print(indent + "  ");
    body_else->print(indent + "  ");
}