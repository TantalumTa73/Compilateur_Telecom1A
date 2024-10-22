#pragma once
#include <string>
#include "define.hpp"

enum TokenType {
    
    // Root
    ROOT,
    UNKNOW,

    // GSmt
    // G_STMT,
    G_FUN_DEF,
    G_VAR_DEF,

    // Arg
    ARG,
    
    // Stmt
    STMT,
    SCOPE,
    RETURN,
    FOR,
    WHILE,
    VAR_DEF,
    VAR_SET,
    EXPR_STMT,
    IF,
    IF_ELSE,
    
    // Litteral
    // LITTERAL,
    LITTERAL_INT,
    LITTERAL_CHAR,
    LITTERAL_BOOL,
    
    // LeftValue
    // LEFT_VALUE,
    ARRAY,
    VAR,
    
    // Expr
    // EXPR,
    CONST,
    VAR_GET,
    LIST,
    FUN_CALL,
    LEFT_VAL_OP,
    UNIOP,
    BINOP,
    TERNOP
};


enum DataType {
    VOID,
    INT,
    CHAR,
    BOOL,
    // ARRAY,
    // PTR
};

TokenType token_type(string s);
DataType data_type(string s);
string show(TokenType t);