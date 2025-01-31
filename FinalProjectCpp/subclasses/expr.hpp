#pragma once
#include <vector>
#include "../token.hpp"
#include "assembly.hpp"

class Expr : public Token {
    public:
        bool is_bool = false;
        Expr(TokenType t) : Token(t) {}
        virtual void print(string indent = "") override;
};


class ValueGet : public Expr {
    public:
        LeftValue* value;
        bool is_address;
        ValueGet() : Expr(VALUE_GET) {
            value = nullptr;
        };
        ValueGet(LeftValue* value, bool is_address) : Expr(VALUE_GET) {
            this->value = value;
            this->is_address = is_address;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children() override {
            return {(Tk)value};
        }
};

class List : public Expr {
    public:
        vector<Expr*> values;
        List() : Expr(LIST) {
            values = vector<Expr*>();
        };
        List(vector<Expr*> values) : Expr(LIST) {
            this->values = values;
        };
        void print(string indent = "") override;
        void on_enter() override;
        vector<Tk> children() override {
            vector<Tk> res;
            for (auto v : values) {
                res.push_back((Tk)v);
            }
            return res;
        }
};

class SizeOf : public Expr {
    public:
    DataType type;
    SizeOf(string type_name) : Expr(SIZE_OF) {
        type = data_type(type_name);
    }
    void on_enter() override;
};

class FunCall : public Expr {
    public:
        string name;
        vector<Expr*> args;
        FunCall() : Expr(FUN_CALL) {
            name = "";
            args = vector<Expr*>();
        };
        FunCall(string name, vector<Expr*> args) : Expr(FUN_CALL) {
            this->name = name;
            this->args = args;
        };
        void print(string indent = "") override;
        void on_enter() override;
        void on_exit() override;
        vector<Tk> children() override {
            vector<Tk> res;
            for (auto it = args.rbegin(); it != args.rend(); ++it) {
                res.push_back((Tk)*it);
            }
            return res;
        }
};


class LRop : public Expr {
    public:
        string op;
        LeftValue* left_value;
        
        LRop(string op, LeftValue* left_value) : Expr(LR_OP) {
            this->op = op;
            this->left_value = left_value;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)left_value};
        }
        void on_exit() override;
};

class Uniop : public Expr {
    public:
        string uniop;
        Expr* value;
        Uniop() : Expr(UNIOP) {
            uniop = "";
            value = nullptr;
        };
        Uniop(string uniop, Expr* value) : Expr(UNIOP) {
            this->uniop = uniop;
            this->value = value;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)value};
        }
        void on_exit() override;
};

class Binop : public Expr {
    public:
        string binop;
        Expr* v1;
        Expr* v2;


        Binop(string binop, Expr* v1, Expr* v2) : Expr(BINOP) {
            this->binop = binop;
            this->v1 = v1;
            this->v2 = v2;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children() override {
            return {(Tk)v1, (Tk)v2};
        }
};

class LazyAnd : public Expr {
    public:
        Expr* v1;
        Expr* v2;

        Jnz* goto_set = nullptr;
        CmdX86* cmd_not_set = nullptr;
        Jmp* goto_end = nullptr ;
        Label* label_end = nullptr ;
        Label* label_set = nullptr ;

        LazyAnd(Expr* v1, Expr* v2, int label) : Expr(LAZY_AND) {
            this->v1 = v1;
            this->v2 = v2;
            v1->is_bool = true;
            v2->is_bool = true;
            goto_set = new Jnz("L" + to_string(label) + "_set");
            cmd_not_set = new CmdX86("pushq $0");
            goto_end = new Jmp("L" + to_string(label) + "_end_set");
            label_end = new Label("L" + to_string(label) + "_end_set");
            label_set = new Label("L" + to_string(label) + "_set");
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {
                (Tk) v1, (Tk) goto_set, 
                (Tk) cmd_not_set, (Tk) goto_end, 
                (Tk) label_set, (Tk) v2, (Tk) label_end
            };
            
        }
};
class LazyOr : public Expr {
    public:
        Expr* v1;
        Expr* v2;

        Jz* goto_set ;
        CmdX86* cmd_not_set ;
        Jmp* goto_end ;
        Label* label_end  ;
        Label* label_set  ;

        LazyOr(Expr* v1, Expr* v2, int label) : Expr(LAZY_OR) {
            this->v1 = v1;
            this->v2 = v2;
            v1->is_bool = true;
            v2->is_bool = true;
            goto_set = new Jz("L" + to_string(label) + "_set");
            label_set = new Label("L" + to_string(label) + "_set");
            cmd_not_set = new CmdX86("pushq $1");
            goto_end = new Jmp("L" + to_string(label) + "_end_set");
            label_end = new Label("L" + to_string(label) + "_end_set");
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {
                (Tk) v1, (Tk) goto_set, 
                (Tk) cmd_not_set, (Tk) goto_end, 
                (Tk) label_set, (Tk) v2, (Tk) label_end
            };
            
        }
};

class Ternop : public Expr {
    public:
        Expr* condition;
        Expr* v1;
        Expr* v2;
        Ternop() : Expr(TERNOP) {
            condition = nullptr;
            v1 = nullptr;
            v2 = nullptr;
        };
        Ternop(Expr* condition, Expr* v1, Expr* v2) : Expr(TERNOP) {
            this->condition = condition;
            this->v1 = v1;
            this->v2 = v2;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)condition, (Tk)v1, (Tk)v2};
        }
        void on_exit() override;
};