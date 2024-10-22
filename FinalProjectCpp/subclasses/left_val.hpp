#pragma once
#include "../token.hpp"

class LeftValue : public Token {
    public:
        LeftValue(TokenType t) : Token(t) {};
        void print(string indent = "") override ;
        virtual string get_id() = 0;
};

class Var : public LeftValue {
    public:
        string name;
        Var() : LeftValue(VAR) {
            name = "";
        };
        Var(string name) : LeftValue(VAR) {
            this->name = name;
        };
        void print(string indent = "") override;
        string get_id() override {return name;}
        vector<Tk> children() override {
            return {};
        }
};

class Array : public LeftValue {
    public:
        LeftValue* left_value;
        Expr* index;
        Array() : LeftValue(ARRAY) {
            left_value = nullptr;
            index = nullptr;
        };
        Array(LeftValue* left_value, Expr* index) : LeftValue(ARRAY) {
            this->left_value = left_value;
            this->index = index;
        };
        void print(string indent = "") override;
        string get_id() override {
            ERROR("Array get_id() not implemented");
        }
        vector<Tk> children() override {
            return {(Tk)left_value, (Tk)index};
        }
};