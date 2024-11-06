#pragma once
#include "../token.hpp"

class Litteral : public Expr {
    public:
        Litteral(TokenType t) : Expr(t) {}
        void print(string indent = "") override {
            v_cout << indent << "Litteral: " << "\n";
        }
};

class Void : public Litteral {
    public:
        Void() : Litteral(LITTERAL_VOID){}
        void print(string indent = "") override {
            v_cout << indent << "Void\n";
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
            v_cout << indent << "Int: " << value << "\n";
        }
        void on_enter() override;
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
            v_cout << indent << "Char: " << value << "\n";
        }
        void on_enter() override;
};
class String : public Litteral {
    public:
        string value;
        int string_id;
        int length;
        String(string value, int string_id, int length) : Litteral(LITTERAL_STRING){
            this->value = value;
            this->string_id = string_id;
            this->length = length;
        }
        void print(string indent = "") override {
            v_cout << indent << "String: " << value << " (" << length << ")\n";
        }
        void on_enter() override;
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
            v_cout << indent << "Bool: " << value << "\n";
        }
        void on_enter() override;
};