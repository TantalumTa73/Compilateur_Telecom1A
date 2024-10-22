#pragma once
#include "../token.hpp"

class Arg : public Token {
    public:
        string name;
        string type;
        Arg() : Token(ARG) {
        // Arg() {
            // tk_type = ARG;
            name = "";
            type = "";
        };
        Arg(string name, string type){
            this->name = name;
            this->type = type;
        };
        void print(string indent = "") override {
            v_cout << indent << "Arg: " << name << " " << type << "\n";
        }
        vector<Tk> children() override {
            return {};
        }
};