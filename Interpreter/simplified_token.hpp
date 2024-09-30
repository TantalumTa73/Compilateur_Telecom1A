#pragma once
#include <vector>
#include <string>

#include "token.hpp"

class SimplifiedToken {
    public:
        const int start_line ;
        const int start_char ;
        const int end_line ;
        const int end_char ;
        
        SimplifiedToken() : 
            start_line(0), start_char(0), end_line(0), end_char(0) {}
        SimplifiedToken(Token t) : 
            start_line(t.start_line), start_char(t.start_char), 
            end_line(t.end_line), end_char(t.end_char) {}

};

class VarDef : public SimplifiedToken {
    public:
        std::string var_name ;
        VarDef(Token t, std::string var_name) : var_name(var_name), SimplifiedToken(t) {}
};
class FunctionDef : public SimplifiedToken {
    public:
        std::string fun_name ;
        std::string arg ;
        std::vector<SimplifiedToken> body ;
        FunctionDef(Token t, std::string fun_name, std::string arg, std::vector<SimplifiedToken> body) : 
            fun_name(fun_name), arg(arg), body(body), SimplifiedToken(t) {}
};
class VarSet : public SimplifiedToken {
    public:
        std::string var_name ;
        VarSet(Token t, std::string var_name) : var_name(var_name), SimplifiedToken(t) {}
};
class FunctionCall : public SimplifiedToken {
    public:
        std::string name ;
        std::string arg_name ;
        FunctionCall(Token t, std::string name, std::string arg_name) : name(name), arg_name(arg_name), SimplifiedToken(t) {}
};
class Calc : public SimplifiedToken {
    public:
        std::string type ;
        int nb_args ;
        Calc(Token t, std::string type, int nb_args) : type(type), nb_args(nb_args), SimplifiedToken(t) {}
};
class Return : public SimplifiedToken {
    public:
        Return(Token t) : SimplifiedToken(t) {}
};

SimplifiedToken simplify(Token token);
std::vector<SimplifiedToken> simplify(std::vector<Token> token);