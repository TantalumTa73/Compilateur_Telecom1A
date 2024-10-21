#pragma once
#include "../token.hpp"

class LeftValue : public Token {
    public:
        LeftValue(){};
        void print(string indent = "") override ;
};

class Var : public LeftValue {
    public:
        string name;
        Var(){
            name = "";
        };
        Var(string name){
            this->name = name;
        };
        void print(string indent = "") override;
};

class Array : public LeftValue {
    public:
        LeftValue* left_value;
        Expr* index;
        Array(){
            left_value = nullptr;
            index = nullptr;
        };
        Array(LeftValue* left_value, Expr* index){
            this->left_value = left_value;
            this->index = index;
        };
        void print(string indent = "") override;
};