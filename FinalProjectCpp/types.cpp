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
