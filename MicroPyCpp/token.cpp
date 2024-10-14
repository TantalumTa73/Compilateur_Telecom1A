

#include "token.hpp"

void Token::print(string indent) {
    switch (type) {
        case UNDEFINED : {cout << "printType : UNDEFINED\n"; return;}
        case ROOT : return ((Root*) this)->print(indent);
        case SCOPE : return ((Scope*) this)->print(indent);
        case FUN_DEF : return ((FunDef*) this)->print(indent);
        case LOOP_FOR : return ((LoopFor*) this)->print(indent);

        case STMT : return ((Stmt*) this)->print(indent);
        case EXPR : return ((Expr*) this)->print(indent);
        case LITTERAL : return ((Litteral*) this)->print(indent);

        case RETURN : return ((Return*) this)->print(indent);
        case VAR_SET : return ((VarSet*) this)->print(indent);

        case VAR : return ((Var*) this)->print(indent);
        case LIST_ELM : return ((ListElm*) this)->print(indent);

        case UNIOP : return ((Uniop*) this)->print(indent);
        case BINOP : return ((Binop*) this)->print(indent);
        case LIST_GET : return ((ListGet*) this)->print(indent);
        case CALL : return ((Call*) this)->print(indent);
        case VAR_GET : return ((VarGet*) this)->print(indent);
        
        case LIST : return ((List*) this)->print(indent);
        case INT : return ((Int*) this)->print(indent);
        case FLOAT : return ((Float*) this)->print(indent);
        case STRING : return ((String*) this)->print(indent);
        case BOOL : return ((Bool*) this)->print(indent);
        case NONE : return ((None*) this)->print(indent);
        default: {cout << "Error: unknown type\n"; return;}
    } 
}


void Stmt::print(string indent) {
    cout << indent << "Stmt\n";
    // cout << indent << type_name(type) << "\n";
    if (next != nullptr) {
        next->print(indent + "\t");
    }
}

void Expr::print(string indent) {
    cout << indent << "Expr\n";
    if (next != nullptr) {
        next->print(indent + "\t");
    }
}



void Root::print(string indent) {
    cout << indent << "Root\n";
    int i = 0;
    for (Token* fun : funs) {
        cout << indent+"\t" << "[" << i++ << "]\n";
        fun->print(indent + "\t\t");
    }
}