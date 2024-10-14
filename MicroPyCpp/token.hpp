#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "types.hpp"


class Pos{
    public:
        int start_line = 0;
        int start_char = 0;
        int end_line = 0;
        int end_char = 0;
};

class Token {
    public:
        Type type;
        Pos pos = Pos();
        Token(Type type) : type(type) {}
        Token() : type(UNDEFINED) {}
        virtual ~Token() {}

        void print(string indent = "");
        
        void printType(string indent = "") {
            cout << indent << "Token of type " << type_name(type) << "\n";
        }

        void printPos(string indent = "") {
            cout << indent << "Pos: " << pos.start_line << ":" << pos.start_char << " - " << pos.end_line << ":" << pos.end_char << "\n";
        }
};



// General

class Stmt : public Token {
    public:
        // Stmt* next = nullptr;
        Token* next = nullptr;
        Stmt(Type T) : Token(T) {}
        void print(string indent);

};

class Expr : public Stmt {
    public:
        Token* next = nullptr;
        // Expr* next = nullptr;
        Expr(Type T) : Stmt(T) {}
        void print(string indent);

};



class Scope : public Token {
    public:
        vector<Stmt*> body ;
        Scope() : Token(SCOPE) {}
        void print(string indent = "") {
            cout << indent << "Scope\n";
            for (Stmt* stmt : body) {
                stmt->print(indent + "\t");
            }
        }
};

class FunDef : public Token {
    public:
        string name ;
        vector<Expr> args ;
        Scope body ;
        FunDef() : Token(FUN_DEF) {}
};

class Root : public Token {
    public:
        vector<Token*> funs ;
        Root() : Token(ROOT) { funs = vector<Token*>(); }
        void print(string indent);
};



// Stmt

class LoopFor : public Stmt {
    public:
        string varname ;
        Scope body ;
        LoopFor() : Stmt(LOOP_FOR) {}
};

class Return : public Stmt {
    public:
        Expr value = Expr(UNDEFINED);
        Return() : Stmt(RETURN) {}
};

class LeftVal : public Token {
    public:
        LeftVal(Type T) : Token(T) {}
};

class VarSet : public Stmt {
    public:
        LeftVal left_value = LeftVal(UNDEFINED);
        Expr value = Expr(UNDEFINED);
        VarSet() : Stmt(VAR_SET) {}
};


// Left Value



class Var : public LeftVal {
    public:
        string name ;
        Var() : LeftVal(VAR) {}
};

class ListElm : public LeftVal {
    public:
        string name ;
        Expr index = Expr(UNDEFINED);
        ListElm() : LeftVal(LIST_ELM) {}
};

// Expr

class Uniop : public Expr {
    public:
        string op ;
        Expr value = Expr(UNDEFINED);
        Uniop() : Expr(UNIOP) {}
};

class Binop : public Expr {
    public:
        string op ;
        Expr left = Expr(UNDEFINED);
        Expr right = Expr(UNDEFINED);
        Binop() : Expr(BINOP) {}
};

class ListGet : public Expr {
    public:
        string name ;
        Expr index = Expr(UNDEFINED);
        ListGet() : Expr(LIST_GET) {}
};

class Call : public Expr {
    public:
        string fun_name ;
        vector<Expr> args ;
        Call() : Expr(CALL) {}

};

class VarGet : public Expr {
    public:
        LeftVal left_value = LeftVal(UNDEFINED);
        Expr value = Expr(UNDEFINED);
        VarGet() : Expr(VAR_GET) {}
};

class Litteral : public Expr {
    public :
        Token* next = nullptr;
        // Litteral *next = nullptr;
        Litteral(Type T) : Expr(T) {}

        void print(string indent = "") {
            cout << indent << "Litteral\n";
            if (next != nullptr) {
                next->print(indent + "\t");
            }
        }
};

// Litteral

class List : public Litteral {
    public:
        string name = "";
        vector<Expr> values ;
        List() : Litteral(LIST) {values = vector<Expr>();}
};

class Int : public Litteral {
    public:
        int value = 0;
        Int() : Litteral(INT) {}

        void print(string indent = "") {
            cout << indent << "Int: " << value << "\n";
        }
};

class Float : public Litteral {
    public:
        float value = 0.0;
        Float() : Litteral(FLOAT) {}
};

class String : public Litteral {
    public:
        string value = "";
        String() : Litteral(STRING) {}
};

class Bool : public Litteral {
    public:
        bool value = false ;
        Bool() : Litteral(BOOL) {}
};

class None : public Litteral {
    public:
        None() : Litteral(NONE) {}
};

