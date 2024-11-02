#pragma once
#include <assert.h>
#include "../token.hpp"
#include "expr.hpp"

class LeftValue : public Token {
    public:
        LeftValue(TokenType t) : Token(t) {};
        void print(string indent = "") override ;
        // virtual string get_id() = 0;
        // virtual string get_address(int shift = 0) = 0;
};

class VarGet : public LeftValue {
    public:
        string name;
        // VarGet() : LeftValue(VAR_GET) {
        //     name = "";
        // };
        VarGet(string name) : LeftValue(VAR_GET) {
            this->name = name;
        };
        void print(string indent = "") override;
        // string get_address(int shift = 0) override;
        void on_exit() override;
        vector<Tk> children(string) override {
            return {};
        }
};

class ArrayGet : public LeftValue {
    public:
        LeftValue* left_value;
        Expr* index;
        // ArrayGet() : LeftValue(ARRAY_GET) {
        //     left_value = nullptr;
        //     index = nullptr;
        // };
        ArrayGet(LeftValue* left_value, Expr* index) : LeftValue(ARRAY_GET) {
            this->left_value = left_value;
            this->index = index;
            // ERROR("ArrayGet not implemented");
        };
        void print(string indent = "") override;
        // string get_address(int shift = 0) override;
        void on_exit() override;
        vector<Tk> children(string) override {
            // if (index->tk_type == LITTERAL_INT)
            //     return {};
            return {(Tk)left_value, (Tk)index};
        }
        
};

class LLop : public LeftValue {
    public:
        LeftValue* left_value;
        string op;
        // LLop() : LeftValue(LL_OP) {
        //     left_value = nullptr;
        //     op = "";
        // };
        LLop(LeftValue* left_value, string op) : LeftValue(LL_OP) {
            this->left_value = left_value;
            this->op = op;
        };
        void print(string indent = "") override;
        // string get_address(int shift = 0) override;
        void on_exit() override;
        vector<Tk> children(string) override {
            return {(Tk)left_value};
        }
        
};

class RLop : public LeftValue {
    public:
        string op;
        Expr* value;
        // RLop() : LeftValue(RL_OP) {
        //     op = "";
        //     value = nullptr;
        // };
        RLop(string op, Expr* value) : LeftValue(RL_OP) {
            assert(value != nullptr);
            this->op = op;
            this->value = value;
        };
        void print(string indent = "") override;
        // string get_address(int shift = 0) override;
        void on_exit() override;
        vector<Tk> children(string) override {
            return {(Tk)value};
        }
        
};