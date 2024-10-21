#pragma once
#include "../token.hpp"

class Expr : public Token {
    public:
        Expr(TokenType t) : Token(t) {}
        virtual void print(string indent = "") override;
};

class Const : public Expr {
    public:
        Litteral* value;
        Const() : Expr(CONST) {
            value = nullptr;
        };
        Const(Litteral* value) : Expr(CONST) {
            this->value = value;
        };
        void print(string indent = "") override;
};

class VarGet : public Expr {
    public:
        LeftValue* value;
        VarGet() : Expr(VAR_GET) {
            value = nullptr;
        };
        VarGet(LeftValue* value) : Expr(VAR_GET) {
            this->value = value;
        };
        void print(string indent = "") override;
};

class List : public Expr {
    public:
        vector<Expr*> values;
        List() : Expr(LIST) {
            values = vector<Expr*>();
        };
        List(vector<Expr*> values) : Expr(LIST) {
            this->values = values;
        };
        void print(string indent = "") override;
};

class FunCall : public Expr {
    public:
        string name;
        vector<Expr*> args;
        FunCall() : Expr(FUN_CALL) {
            name = "";
            args = vector<Expr*>();
        };
        FunCall(string name, vector<Expr*> args) : Expr(FUN_CALL) {
            this->name = name;
            this->args = args;
        };
        void print(string indent = "") override;
};

class LeftValOp : public Expr {
    public:
        LeftValue* left_value;
        string op;
        LeftValOp() : Expr(LEFT_VAL_OP) {
            left_value = nullptr;
            op = "";
        };
        LeftValOp(LeftValue* left_value, string op) : Expr(LEFT_VAL_OP) {
            this->left_value = left_value;
            this->op = op;
        };
        void print(string indent = "") override;
};

class Uniop : public Expr {
    public:
        string uniop;
        Expr* value;
        Uniop() : Expr(UNIOP) {
            uniop = "";
            value = nullptr;
        };
        Uniop(string uniop, Expr* value) : Expr(UNIOP) {
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
        Binop() : Expr(BINOP) {
            binop = "";
            v1 = nullptr;
            v2 = nullptr;
        };
        Binop(string binop, Expr* v1, Expr* v2) : Expr(BINOP) {
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
        Ternop() : Expr(TERNOP) {
            condition = nullptr;
            v1 = nullptr;
            v2 = nullptr;
        };
        Ternop(Expr* condition, Expr* v1, Expr* v2) : Expr(TERNOP) {
            this->condition = condition;
            this->v1 = v1;
            this->v2 = v2;
        };
        void print(string indent = "") override;
};