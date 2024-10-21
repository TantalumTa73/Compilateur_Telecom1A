#pragma once
#include "../token.hpp"

class Expr : public Token {
    public:
        Expr(){}
        virtual void print(string indent = "") override;
};

class Const : public Expr {
    public:
        Litteral* value;
        Const(){
            value = nullptr;
        };
        Const(Litteral* value){
            this->value = value;
        };
        void print(string indent = "") override;
};

class VarGet : public Expr {
    public:
        LeftValue* value;
        VarGet(){
            value = nullptr;
        };
        VarGet(LeftValue* value){
            this->value = value;
        };
        void print(string indent = "") override;
};

class List : public Expr {
    public:
        vector<Expr*> values;
        List(){
            values = vector<Expr*>();
        };
        List(vector<Expr*> values){
            this->values = values;
        };
        void print(string indent = "") override;
};

class FunCall : public Expr {
    public:
        string name;
        vector<Expr*> args;
        FunCall(){
            name = "";
            args = vector<Expr*>();
        };
        FunCall(string name, vector<Expr*> args){
            this->name = name;
            this->args = args;
        };
        void print(string indent = "") override;
};

class LeftValOp : public Expr {
    public:
        LeftValue* left_value;
        string op;
        LeftValOp(){
            left_value = nullptr;
            op = "";
        };
        LeftValOp(LeftValue* left_value, string op){
            this->left_value = left_value;
            this->op = op;
        };
        void print(string indent = "") override;
};

class Uniop : public Expr {
    public:
        string uniop;
        Expr* value;
        Uniop(){
            uniop = "";
            value = nullptr;
        };
        Uniop(string uniop, Expr* value){
            this->uniop = uniop;
            this->value = value;
        };
        void print(string indent = "") override;
};

class Binop : public Expr {
    public:
        string binop;
        Expr* v1;
        Expr* v2;
        Binop(){
            binop = "";
            v1 = nullptr;
            v2 = nullptr;
        };
        Binop(string binop, Expr* v1, Expr* v2){
            this->binop = binop;
            this->v1 = v1;
            this->v2 = v2;
        };
        void print(string indent = "") override;
};

class Ternop : public Expr {
    public:
        Expr* condition;
        Expr* v1;
        Expr* v2;
        Ternop(){
            condition = nullptr;
            v1 = nullptr;
            v2 = nullptr;
        };
        Ternop(Expr* condition, Expr* v1, Expr* v2){
            this->condition = condition;
            this->v1 = v1;
            this->v2 = v2;
        };
        void print(string indent = "") override;
};