#include "types.hpp"

TokenType token_type(string s){

    // Root
    if (s == "root") return ROOT;

    // GSmt
    if (s == "fundef") return G_FUN_DEF;
    if (s == "gvardef") return G_VAR_DEF;

    // Arg
    if (s == "arg") return ARG;

    // Stmt
    if (s == "scope") return SCOPE;
    if (s == "return") return RETURN;
    if (s == "keyword") return KEYWORD;
    if (s == "for") return FOR;
    if (s == "while") return WHILE;
    if (s == "vardef") return VAR_DEF;
    if (s == "varset") return VAR_SET;
    if (s == "expr") return EXPR_STMT;
    if (s == "if") return IF;
    if (s == "ifelse") return IF_ELSE;

    // Litteral
    if (s == "int") return LITTERAL_INT;
    if (s == "char") return LITTERAL_CHAR;
    if (s == "bool") return LITTERAL_BOOL;

    // LeftValue
    if (s == "varget") return VAR_GET;
    if (s == "arrayget") return ARRAY_GET;
    if (s == "llop") return LL_OP;
    if (s == "rlop") return RL_OP;

    // Expr
    if (s == "const") return LITTERAL;
    if (s == "valueget") return VALUE_GET;
    if (s == "list") return LIST;
    if (s == "funcall") return FUN_CALL;
    if (s == "lralop") return LR_OP;
    if (s == "uniop") return UNIOP;
    if (s == "binop") return BINOP;
    if (s == "ternop") return TERNOP;

    ERROR("token_type : unknow token " + s  + "\n");

}

DataType data_type(string s){
    if (s == "void") return VOID;
    if (s == "int") return INT;
    if (s == "char") return CHAR;
    if (s == "bool") return BOOL;
    // if (s == "array") return ARRAY;
    if (s == "int*") return PTR;
    if (s == "ptr") return PTR;
    ERROR("Error in DataType : unknown type " + s + "\n");
}

std::ostream &operator<<(std::ostream &os, DataType const &t) { 
    switch (t){
        case VOID: return os << "void";
        case INT: return os << "int";
        case CHAR: return os << "char";
        case BOOL: return os << "bool";
        case PTR: return os << "ptr";
    }
}

std::ostream &operator<<(std::ostream &os, TokenType const &t) { 
    switch (t){
        case ROOT: return os << "root";
        case UNKNOW: return os << "unknow";

        case G_FUN_DEF: return os << "fundef";
        case G_VAR_DEF: return os << "gvardef";

        case ARG: return os << "arg";

        case STMT: return os << "stmt";
        case SCOPE: return os << "scope";
        case RETURN: return os << "return";
        case KEYWORD: return os << "keyword";
        case FOR: return os << "for";
        case WHILE: return os << "while";
        case VAR_DEF: return os << "vardef";
        case VAR_SET: return os << "varset";
        case EXPR_STMT: return os << "expr";
        case IF: return os << "if";
        case IF_ELSE: return os << "ifelse";

        case LITTERAL_VOID: return os << "void";
        case LITTERAL_INT: return os << "int";
        case LITTERAL_CHAR: return os << "char";
        case LITTERAL_BOOL: return os << "bool";

        case VAR_GET: return os << "varget";
        case ARRAY_GET: return os << "arrayget";
        case LL_OP: return os << "llop";
        case RL_OP: return os << "rlop";

        case LITTERAL: return os << "const";
        case VALUE_GET: return os << "valueget";
        case LIST: return os << "list";
        case FUN_CALL: return os << "funcall";
        case LR_OP: return os << "leftvalop";
        case UNIOP: return os << "uniop";
        case BINOP: return os << "binop";
        case TERNOP: return os << "ternop";

        case JZ: return os << "jz";
        case JMP: return os << "jmp";
        case LABEL: return os << "label";
    }
    return os;
}


int type_size(DataType type){
    switch (type){
        case VOID: return 0;
        case INT: return 8;
        case CHAR: return 1;
        case BOOL: return 1;
        case PTR: return 8;
    }
}

