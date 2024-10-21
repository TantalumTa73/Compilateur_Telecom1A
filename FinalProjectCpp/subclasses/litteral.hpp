#pragma once
#include "../token.hpp"

class Litteral : public Token {
    public:
        Litteral(TokenType t) : Token(t) {}
        void print(string indent = "") override {
            std::cout << indent << "Litteral: " << "\n";
        }
};

class Int : public Litteral {
    public:
        int value;
        Int() : Litteral(LITTERAL_INT){
            value = 0;
        }
        Int(int value) : Litteral(LITTERAL_INT){
            this->value = value;
        }
        void print(string indent = "") override {
            std::cout << indent << "Int: " << value << "\n";
        }
};

class Char : public Litteral {
    public:
        char value;
        Char() : Litteral(LITTERAL_CHAR){
            value = '\0';
        }
        Char(char value) : Litteral(LITTERAL_CHAR){
            this->value = value;
        }
        void print(string indent = "") override {
            std::cout << indent << "Char: " << value << "\n";
        }
};

class Bool : public Litteral {
    public:
        bool value;
        Bool() : Litteral(LITTERAL_BOOL){
            value = false;
        }
        Bool(bool value) : Litteral(LITTERAL_BOOL){
            this->value = value;
        }
        void print(string indent = "") override {
            std::cout << indent << "Bool: " << value << "\n";
        }
};