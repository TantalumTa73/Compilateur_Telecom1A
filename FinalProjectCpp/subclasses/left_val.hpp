#pragma once
#include "../token.hpp"

class LeftValue : public Token {
    public:
        LeftValue(TokenType t) : Token(t) {};
        void print(string indent = "") override ;
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
};