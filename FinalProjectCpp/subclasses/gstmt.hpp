#pragma once
#include "../token.hpp"
// #include "arg.hpp"

class GStmt : public Token {
    public:
        GStmt(){}
        virtual void print(string indent = "") override;
};

class GFunDef : public GStmt {
    public:
        string name;
        string type;
        // vector<Arg*> args;
        Stmt* body;
        GFunDef(){
            name = "";
            type = "";
            // args = vector<Arg*>();
            body = nullptr;
        };
        GFunDef(string type, string name, vector<Arg*> args, Stmt* body){
            this->name = name;
            this->type = type;
            // this->args = args;
            this->body = body;
        };
        void print(string indent = "") override;
};

class GVarDef : public GStmt {
    public:
        string type;
        string name;
        Expr* value;
        GVarDef(){
            type = "";
            name = "";
            value = nullptr;
        };
        GVarDef(string type, string name, Expr* value){
            this->type = type;
            this->name = name;
            this->value = value;
        };
        void print(string indent = "") override;
};

