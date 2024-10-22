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
    if (s == "var") return VAR;
    if (s == "array") return ARRAY;

    // Expr
    if (s == "const") return CONST;
    if (s == "varget") return VAR_GET;
    if (s == "list") return LIST;
    if (s == "funcall") return FUN_CALL;
    if (s == "leftvalop") return LEFT_VAL_OP;
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
    // if (s == "ptr") return PTR;
    ERROR("Error in DataType : unknown type " + s + "\n");
}


string show(TokenType t){
    switch (t){
        case ROOT: return "root";
        case UNKNOW: return "unknow";

        case G_FUN_DEF: return "fundef";
        case G_VAR_DEF: return "gvardef";

        case ARG: return "arg";

        case STMT: return "stmt";
        case SCOPE: return "scope";
        case RETURN: return "return";
        case FOR: return "for";
        case WHILE: return "while";
        case VAR_DEF: return "vardef";
        case VAR_SET: return "varset";
        case EXPR_STMT: return "expr";
        case IF: return "if";
        case IF_ELSE: return "ifelse";

        case LITTERAL_VOID: return "void";
        case LITTERAL_INT: return "int";
        case LITTERAL_CHAR: return "char";
        case LITTERAL_BOOL: return "bool";

        case VAR: return "var";
        case ARRAY: return "array";

        case CONST: return "const";
        case VAR_GET: return "varget";
        case LIST: return "list";
        case FUN_CALL: return "funcall";
        case LEFT_VAL_OP: return "leftvalop";
        case UNIOP: return "uniop";
        case BINOP: return "binop";
        case TERNOP: return "ternop";
    }
    return "" ;
}