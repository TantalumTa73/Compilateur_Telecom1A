#pragma once
#include <string>
#include <vector>

#include "JSON.hpp"

class Token ;
using Tk = Token*;

class Token {

    public:

        string type;

        Token();
        Token(JSON* json);  

        virtual void print() ;
};

class GStmt ;
class Stmt ;
class Expr ;
class Litteral ;
class LeftValue ;
class Arg ;