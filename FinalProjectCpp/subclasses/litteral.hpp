#pragma once
#include "../token.hpp"

class Litteral : public Token {
    public:
        Litteral(){}
        void print(string indent = "") override {
            std::cout << indent << "Litteral: " << "\n";
        }
};

class Int : public Litteral {
    public:
        int value;
        Int(){
            value = 0;
        }
        Int(int value){
            this->value = value;
        }
        void print(string indent = "") override {
            std::cout << indent << "Int: " << value << "\n";
        }
};

class Char : public Litteral {
    public:
        char value;
        Char(){
            value = '\0';
        }
        Char(char value){
            this->value = value;
        }
        void print(string indent = "") override {
            std::cout << indent << "Char: " << value << "\n";
        }
};

class Bool : public Litteral {
    public:
        bool value;
        Bool(){
            value = false;
        }
        Bool(bool value){
            this->value = value;
        }
        void print(string indent = "") override {
            std::cout << indent << "Bool: " << value << "\n";
        }
};