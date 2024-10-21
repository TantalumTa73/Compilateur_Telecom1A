#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "functions.hpp"
#include "data.hpp"

extern std::unordered_map<std::string, Function> functions;
extern std::vector<std::string> called_fun_names;


enum TokenType {
    RETURN,
    DEF_VAR,
    DEF_FUN,
    CALL_FUN,
    SET_VAR,
    GET_VAR,
    CST,
    OP,
    PARENTHESIS,
    UNDEFINED
};

class RawToken {
    public:
    int start_line;
    int start_char;
    int end_line;
    int end_char;
    RawToken* parent;
    std::vector<RawToken> children;
    std::unordered_map<std::string, std::string> attributes;

    RawToken();
    RawToken(std::string name, int start_line, int start_char, int end_line, int end_char);

    void set_attribute(std::string key, std::string value);
    std::string get_attribute(std::string key);
    void add_child(RawToken child);
};

class Token {
    public:
        TokenType id;
        std::string name;
        int start_line ;
        int start_char ;
        int end_line ;
        int end_char ;
        int remained_children;
        Token* parent ;
        std::vector<Token*> children;

        Token();
        Token(std::string name, int start_line, int start_char, int end_line, int end_char, TokenType id) ;

        virtual ~Token() {};

        void add_child(Token* child);

        virtual void on_enter() = 0;
        virtual void on_exit() = 0;

    protected:
        Variable find_var(std::string var_name);
};

class ReturnToken : public Token{
    public:
        ReturnToken(std::string name, int start_line, int start_char, int end_line, int end_char);

        void on_enter() override;
        void on_exit() override;
};

class DefVarToken : public Token{
    public:
        DefVarToken(std::string name, int start_line, int start_char, int end_line, int end_char);

        void on_enter() override ;
        void on_exit() override ;
};

class DefFunToken : public Token{
    public:
        std::vector<std::string> arg_names;

        DefFunToken(std::string name, int start_line, int start_char, int end_line, int end_char, std::vector<std::string> arg_names);

        void on_enter() override ;
        void on_exit() override ;
};

class CallFunToken : public Token{
    public:
        CallFunToken(std::string name, int start_line, int start_char, int end_line, int end_char);
        void on_enter() override ;
        void on_exit() override ;
};

class SetVarToken : public Token{
    public:
        SetVarToken(std::string name, int start_line, int start_char, int end_line, int end_char);
        void on_enter() override ;
        void on_exit() override ;
};

class GetVarToken : public Token{
    public:
        GetVarToken(std::string name, int start_line, int start_char, int end_line, int end_char);
        void on_enter() override ;
        void on_exit() override ;
};

class CstToken : public Token{
    public:
        int value;

        CstToken(std::string name, int start_line, int start_char, int end_line, int end_char, int value);

        void on_enter() override ;
        void on_exit() override ;
};

class OpToken : public Token{
    public:
        std::string op_name;

        OpToken(std::string name, int start_line, int start_char, int end_line, int end_char, std::string op_name);

        void on_enter() override ;
        void on_exit() override ;
};

class ParenthesisToken : public Token{
    public:
        ParenthesisToken(std::string name, int start_line, int start_char, int end_line, int end_char);

        void on_enter() override ;
        void on_exit() override ;
};

class UndefinedToken : public Token{
    public:
        UndefinedToken(std::string name, int start_line, int start_char, int end_line, int end_char);

        void on_enter() override ;
        void on_exit() override ;
};
#endif