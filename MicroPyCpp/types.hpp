#include <string>

using namespace std;

enum Type {

    // General
    UNDEFINED,
    ROOT,
    SCOPE,
    FUN_DEF,
    LOOP_FOR,
    // POS,

    // TEMP
    STMT,
    EXPR,
    LITTERAL,

    // Stmt
    RETURN,
    VAR_SET,

    // Left Value
    VAR,
    LIST_ELM,

    // Expr
    UNIOP,
    BINOP,
    LIST_GET,
    CALL,
    VAR_GET,

    // Litteral
    LIST,
    INT,
    FLOAT,
    STRING,
    BOOL,
    NONE
};

string type_name(Type t);