#pragma once
#include "../token.hpp"

class Stmt : public Token {
    public:
        Stmt(){}
        virtual void print(string indent = "") override;
};

class Sscope : public Stmt {
    public:
        vector<Stmt*> body;
        Sscope(){
            body = vector<Stmt*>();
        };
        Sscope(vector<Stmt*> body){
            this->body = body;
        };
        void print(string indent = "") override;
};

class Sreturn : public Stmt {
    public:
        Expr* value;
        Sreturn(){
            value = nullptr;
        };
        Sreturn(Expr* value){
            this->value = value;
        };
        void print(string indent = "") override;
};

class Sfor : public Stmt {
    public:
        Stmt* init;
        Expr* condition;
        Stmt* increment;
        Stmt* body;
        Sfor(){
            init = nullptr;
            condition = nullptr;
            increment = nullptr;
            body = nullptr;
        };
        Sfor(Stmt* init, Expr* condition, Stmt* increment, Stmt* body){
            this->init = init;
            this->condition = condition;
            this->increment = increment;
            this->body = body;
        };
        void print(string indent = "") override;
};

class Swhile : public Stmt {
    public:
        Expr* condition;
        Stmt* body;
        Swhile(){
            condition = nullptr;
            body = nullptr;
        };
        Swhile(Expr* condition, Stmt* body){
            this->condition = condition;
            this->body = body;
        };
        void print(string indent = "") override;
};

class SvarDef : public Stmt {
    public:
        string type;
        string name;
        Expr* value;
        SvarDef(){
            type = "";
            name = "";
            value = nullptr;
        };
        SvarDef(string type, string name, Expr* value){
            this->type = type;
            this->name = name;
            this->value = value;
        };
        void print(string indent = "") override;
};

class SvarSet : public Stmt {
    public:
        LeftValue* left_value;
        string op;
        Expr* value;
        SvarSet(){
            left_value = nullptr;
            op = "";
            value = nullptr;
        };
        SvarSet(LeftValue* left_value, string op, Expr* value){
            this->left_value = left_value;
            this->op = op;
            this->value = value;
        };
        void print(string indent = "") override;
};

class Sexpr : public Stmt {
    public:
        Expr* value;
        Sexpr(){
            value = nullptr;
        };
        Sexpr(Expr* value){
            this->value = value;
        };
        void print(string indent = "") override;
};

class Sif : public Stmt {
    public:
        Expr* condition;
        Stmt* body;
        Sif(){
            condition = nullptr;
            body = nullptr;
        };
        Sif(Expr* condition, Stmt* body){
            this->condition = condition;
            this->body = body;
        };
        void print(string indent = "") override;
};

class SifElse : public Stmt {
    public:
        Expr* condition;
        Stmt* body_if;
        Stmt* body_else;
        SifElse(){
            condition = nullptr;
            body_if = nullptr;
            body_else = nullptr;
        };
        SifElse(Expr* condition, Stmt* body_if, Stmt* body_else){
            this->condition = condition;
            this->body_if = body_if;
            this->body_else = body_else;
        };
        void print(string indent = "") override;
};

