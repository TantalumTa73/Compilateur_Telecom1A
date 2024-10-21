#pragma once
#include "../token.hpp"

class Arg : public Token {
    public:
        string name;
        string type;
        Arg(){
            name = "";
            type = "";
        };
        Arg(string name, string type){
            this->name = name;
            this->type = type;
        };
        void print(string indent = "") override {
            std::cout << indent << "Arg: " << name << " " << type << "\n";
        }
};