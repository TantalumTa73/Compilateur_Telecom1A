#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory> 

#include "token.hpp"

class SimplifiedToken ; 
using TkPtr = SimplifiedToken*;


enum TkType {
    VOID,
    VAR_DEF,
    FUNCTION_DEF,
    VAR_SET,
    FUNCTION_CALL,
    CONSTANT,
    VAR_GET,
    OPERATOR,
    RETURN,
    UNDEFINED
};

class SimplifiedToken {
    public:
        int start_line ;
        int start_char ;
        int end_line ;
        int end_char ;
        
        TkType type = UNDEFINED;

        virtual void print(std::string indent = "") = 0 ;
        // {
        //     v_cout << indent << "SimplifiedToken(" << type << ")\n";
        // }
        
        SimplifiedToken() : 
            start_line(0), start_char(0), end_line(0), end_char(0), type(VOID) {}
        SimplifiedToken(Token t, TkType type) : 
            start_line(t.start_line), start_char(t.start_char), 
            end_line(t.end_line), end_char(t.end_char), type(type) {}
        SimplifiedToken(TkType type, int l1, int c1, int l2, int c2) : 
            start_line(l1), start_char(c1), end_line(l2), end_char(c2), type(type) {}

        virtual ~SimplifiedToken() = default;

};


class VarDef : public SimplifiedToken {
    public:
        std::string var_name ;
        VarDef(Token t, std::string var_name) : SimplifiedToken(t,VAR_DEF), var_name(var_name) {}
        
        void print(std::string indent = ""){
            v_cout << indent << "VarDef: " << var_name << "\n";
        }

};

class FunctionDef : public SimplifiedToken {
    public:
        std::string fun_name ;
        std::string arg_name ;
        std::vector<TkPtr> body ;
        FunctionDef(Token t, std::string fun_name, std::string arg_name, std::vector<TkPtr> body) : 
            SimplifiedToken(t,FUNCTION_DEF), fun_name(fun_name), arg_name(arg_name), body(body) {}
        
        void print(std::string indent = ""){
            v_cout << indent << "FunctionDef: " << fun_name << "(" << arg_name << ")" << std::endl;
            for (auto& t : body){
                t->print(indent+"\t");
            }
        }
};

class VarSet : public SimplifiedToken {
    public:
        std::string var_name ;
        VarSet(Token t, std::string var_name) : SimplifiedToken(t, VAR_SET), var_name(var_name) {}

        void print(std::string indent = ""){
            v_cout << indent << "VarSet: " << var_name << "\n";
        }
};

class FunctionCall : public SimplifiedToken {
    public:
        std::string name ;
        std::string arg_name ;
        FunctionCall(Token t, std::string name, std::string arg_name) : 
            SimplifiedToken(t,FUNCTION_CALL), name(name), arg_name(arg_name) {}

        void print(std::string indent = ""){
            v_cout << indent << "FunctionCall: " << name << "(" << arg_name << ")\n";
        }

};

class Constant : public SimplifiedToken {
    public:
        int value;
        Constant(Token t, int value) : SimplifiedToken(t, CONSTANT), value(value) {}
        void print(std::string indent = "") {
            v_cout << indent << "Constant : " << value << std::endl;
        }
};

class VarGet : public SimplifiedToken {
    public:
        std::string var_name;
        VarGet(Token t, std::string var_name) : SimplifiedToken(t, VAR_GET), var_name(var_name) {}
        void print(std::string indent = "") {
            v_cout << indent << "VarGet : " << var_name << std::endl;
        }
};

class Operator : public SimplifiedToken {
    public:
        std::string operator_name;
        int nb_args;
        Operator(Token t, std::string op_name, int n) : 
            SimplifiedToken(t, OPERATOR), operator_name(op_name), nb_args(n) {}
        void print(std::string indent = "") {
            v_cout << indent << "Operator: " << operator_name << ", Args: " << nb_args << std::endl;
        }
};

class Return : public SimplifiedToken {
    public:
        Return(Token t) : SimplifiedToken(t, RETURN) {}
        void print(std::string indent = ""){
            v_cout << indent << "Return" << std::endl;
        }
};

TkPtr simplify(Token token);
std::vector<TkPtr> simplify(std::vector<Token> token);