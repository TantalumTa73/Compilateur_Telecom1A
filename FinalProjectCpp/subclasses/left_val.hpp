#pragma once
#include "../token.hpp"

class LeftValue : public Token {
    public:
        LeftValue(TokenType t) : Token(t) {};
        void print(string indent = "") override ;
        virtual string get_id() = 0;
};

class VarGet : public LeftValue {
    public:
        string name;
        VarGet() : LeftValue(VAR_GET) {
            name = "";
        };
        VarGet(string name) : LeftValue(VAR_GET) {
            this->name = name;
        };
        void print(string indent = "") override;
        string get_id() override {return name;}
        vector<Tk> children() override {
            return {};
        }
};

class ArrayGet : public LeftValue {
    public:
        LeftValue* left_value;
        Expr* index;
        ArrayGet() : LeftValue(ARRAY_GET) {
            left_value = nullptr;
            index = nullptr;
        };
        ArrayGet(LeftValue* left_value, Expr* index) : LeftValue(ARRAY_GET) {
            this->left_value = left_value;
            this->index = index;
            ERROR("ArrayGet not implemented");
        };
        void print(string indent = "") override;
        string get_id() override {
            return left_value->get_id() + "[" + "]";
        }
        vector<Tk> children() override {
            return {(Tk)left_value, (Tk)index};
        }
};