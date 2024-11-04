#pragma once
#include <string>
#include "define.hpp"

enum TokenType {
    
    // Root
    ROOT,
    UNKNOW,

    // GSmt
    G_FUN_DEF,
    G_VAR_DEF,

    // Arg
    ARG,
    
    // Stmt
    STMT,
    SCOPE,
    RETURN,
    KEYWORD,
    FOR,
    WHILE,
    VAR_DEF,
    VAR_SET,
    EXPR_STMT,
    IF,
    IF_ELSE,
    
    // Litteral
    LITTERAL_VOID,
    LITTERAL_INT,
    LITTERAL_CHAR,
    LITTERAL_BOOL,
    
    // LeftValue
    ARRAY_GET,
    VAR_GET,
    LL_OP,
    RL_OP,
    
    // Expr
    LITTERAL,
    VALUE_GET,
    LIST,
    FUN_CALL,
    LR_OP,
    UNIOP,
    BINOP,
    TERNOP,

    // Assembly
    CMD_X86,
    JZ,
    JNZ,
    JMP,
    LABEL
};


enum DataType {
    VOID,
    INT,
    CHAR,
    BOOL,
    PTR
};

std::ostream &operator<<(std::ostream &os, TokenType const &t);
std::ostream &operator<<(std::ostream &os, DataType const &t);

DataType data_type(string s);
TokenType token_type(string s);

int type_size(DataType type);
