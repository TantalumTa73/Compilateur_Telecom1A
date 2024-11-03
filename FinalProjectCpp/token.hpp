#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "define.hpp"
#include "JSON.hpp"
#include "types.hpp"
#include "write_assembly.hpp"
#include "context.hpp"

class Token {

    public:

        const TokenType tk_type;
        int remained_children = 0;

        Token() : tk_type(UNKNOW) {}
        Token(TokenType t) : tk_type(t) {}
        // Token(JSON* json);

        static Token* simplify(JSON* json);
    
        virtual void print(string indent = "");

        virtual void on_enter(){
            vv_cout << "enter in " << tk_type << endl;
        }
        virtual void on_exit(){}
        virtual vector<Token*> children(string){return vector<Token*>();}

    private:
        // vector<T> Token::simplify(vector<JSON*>* vect)
        template<typename T>
        static vector<T> simplify(vector<JSON*>* vect);
        static vector<int> simplify_int(vector<JSON*>* vect);
};

using Tk = Token*;

class Root ;

class GStmt ; // abstract
class GFunDef ;
class GVarDef ;

class Arg ;

class Stmt ; // abstract
class Sscope ;
class Sreturn ;
class Skeyword ;
class SvarDef ;
class SvarSet ;
class Sexpr ;
class Sfor ;
class Swhile ;
class Sif ;
class SifElse ;


class Litteral ; // abstract
class Void ;
class Int ;
class Char ;
class Bool ;

class LeftValue ; // abstract
class ArrayGet ;
class VarGet ;
class LLop ;
class RLop ;

class Expr ; // abstract
class Litteral ;
class ValueGet ;
class List ;
class FunCall ;

class LRop ;
class Uniop ;
class Binop ;
class Ternop ;

class Assembly ; // abstract
class Jeq ;
class Jmp ;
class Label ;