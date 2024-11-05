#pragma once
#include <assert.h>
#include "../token.hpp"
#include "expr.hpp"

class LeftValue : public Token {
    public:
        LeftValue(TokenType t) : Token(t) {};
        void print(string indent = "") override ;
};

class VarGet : public LeftValue {
    public:
        string name;
        VarGet(string name) : LeftValue(VAR_GET) {
            this->name = name;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children(string) override {
            return {};
        }
};

class ArrayGet : public LeftValue {
    public:
        LeftValue* left_value;
        Expr* index;
        ArrayGet(LeftValue* left_value, Expr* index) : LeftValue(ARRAY_GET) {
            this->left_value = left_value;
            this->index = index;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children(string) override {
            return {(Tk)left_value, (Tk)index};
        }
        
};

class LLop : public LeftValue {
    public:
        LeftValue* left_value;
        string op;
        LLop(LeftValue* left_value, string op) : LeftValue(LL_OP) {
            this->left_value = left_value;
            this->op = op;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children(string) override {
            return {(Tk)left_value};
        }
        
};

class RLop : public LeftValue {
    public:
        string op;
        Expr* value;
        RLop(string op, Expr* value) : LeftValue(RL_OP) {
            assert(value != nullptr);
            this->op = op;
            this->value = value;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children(string) override {
            return {(Tk)value};
        }
        
};