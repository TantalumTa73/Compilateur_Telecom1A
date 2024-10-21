#pragma once
#include <string>
#include <vector>

#include "JSON.hpp"
#include "types.hpp"

class Token {

    public:

        TokenType type;

        Token(){}
        Token(JSON* json);

        static Token* simplify(JSON* json);
    
        virtual void print(string indent = "");

    private:
        // vector<T> Token::simplify(vector<JSON*>* vect)
        template<typename T>
        static vector<T> simplify(vector<JSON*>* vect);
};

using Tk = Token*;

class Root ;

class GStmt ;
class GFunDef ;
class GVarDef ;

class Arg ;

class Stmt ;
class Sscope ;
class Sreturn ;
class Sfor ;
class Swhile ;
class SvarDef ;
class SvarSet ;
class Sexpr ;
class Sif ;
class SifElse ;

class Litteral ;
class Int ;
class Char ;
class Bool ;

class LeftValue ;
class Array ;
class Var ;

class Expr ;
class Const ;
class VarGet ;
class List ;
class FunCall ;
class LeftValOp ;
class Uniop ;
class Binop ;
class Ternop ;