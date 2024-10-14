#include <string>

#include "types.hpp"

string type_name(Type t){
    switch (t) {
        case UNDEFINED : return "UNDEFINED";
        case ROOT : return "ROOT";
        case SCOPE : return "SCOPE";
        case FUN_DEF : return "FUN_DEF";
        case LOOP_FOR : return "LOOP_FOR";

        case STMT : return "STMT";
        case EXPR : return "EXPR";
        case LITTERAL : return "LITTERAL";

        case RETURN : return "RETURN";
        case VAR_SET : return "VAR_SET";

        case VAR : return "VAR";
        case LIST_ELM : return "LIST_ELM";

        case UNIOP : return "UNIOP";
        case BINOP : return "BINOP";
        case LIST_GET : return "LIST_GET";
        case CALL : return "CALL";
        case VAR_GET : return "VAR_GET";
        
        case LIST : return "LIST";
        case INT : return "INT";
        case FLOAT : return "FLOAT";
        case STRING : return "STRING";
        case BOOL : return "BOOL";
        case NONE : return "NONE";
        default: return "UNKNOWN";
    } 
}
