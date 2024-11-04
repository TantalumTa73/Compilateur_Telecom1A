#pragma once
#include "../token.hpp"

class Assembly : public Token {
    public:
        Assembly(TokenType t) : Token(t) {}
};

class CmdX86 : public Assembly {
    public:
        string cmd;
        CmdX86(string cmd) : Assembly(CMD_X86){
            this->cmd = cmd;
        };
        void print(string indent = "") override;
        void on_enter() override;
};

class Jz : public Assembly {
    public:
        string label;
        Jz(string label) : Assembly(JZ){
            this->label = label;
            // this->body = body;
        };
        void print(string indent = "") override;
        void on_enter() override;
};

class Jnz : public Assembly {
    public:
        string label;
        Jnz(string label) : Assembly(JNZ){
            this->label = label;
        };
        void print(string indent = "") override;
        void on_enter() override;
};


class Jmp : public Assembly {
    public:
        string label;
        Jmp(string label) : Assembly(JMP){
            this->label = label;
        };
        void print(string indent = "") override;
        void on_enter() override;
};

class Label : public Assembly {
    public:
        string label;
        Label(string label) : Assembly(LABEL){
            this->label = label;
        };
        void print(string indent = "") override;
        void on_enter() override;
};