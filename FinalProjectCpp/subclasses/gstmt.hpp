#pragma once
#include "../token.hpp"
#include "arg.hpp"
#include "expr.hpp"

class GStmt : public Token {
    public:
        GStmt(TokenType t) : Token(t) {}
        virtual void print(string indent = "") override;
};

class GFunDef : public GStmt {
    public:
        string name;
        string type;
        vector<Arg*> args;
        Stmt* body;
        GFunDef(string type, string name, vector<Arg*> args, Stmt* body)
        : GStmt(G_FUN_DEF) {
            this->name = name;
            this->type = type;
            this->args = args;
            this->body = body;
        };
        void print(string indent = "") override;
        void on_enter() override;
        void on_exit() override;
        vector<Tk> children() override {
            vector<Tk> res;
            for (auto v : args) {
                res.push_back((Tk) v);
            }
            res.push_back((Tk) body);
            return res;
        }
};

class GVarDef : public GStmt {
    public:
        DataType type;
        string name;
        vector<int> ladder;
        Expr* value;
        GVarDef(DataType type, string name, vector<int> ladder, Expr* value) : 
        GStmt(G_VAR_DEF) {
            this->type = type;
            this->name = name;
            this->ladder = ladder;
            this->value = value;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children() override {
            if (value == nullptr || is_litteral(value->tk_type)) return {};
            ERROR("Global variable inizialization not yet implemented for non litteral values : " + name);
            return {(Tk)value};
        }
};

