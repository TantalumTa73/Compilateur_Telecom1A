#pragma once
#include <vector>
#include "../token.hpp"

class Expr : public Token {
    public:
        Expr(TokenType t) : Token(t) {}
        virtual void print(string indent = "") override;
};

// class Litteral : public Expr {
//     public:
//         Litteral* value;
//         Litteral() : Expr(LITTERAL) {
//             value = nullptr;
//         };
//         Litteral(Litteral* value) : Expr(LITTERAL) {
//             this->value = value;
//         };
//         void print(string indent = "") override;
//         vector<Tk> children() override {
//             return {(Tk)value} ;
//         }
// };

class ValueGet : public Expr {
    public:
        LeftValue* value;
        ValueGet() : Expr(VALUE_GET) {
            value = nullptr;
        };
        ValueGet(LeftValue* value) : Expr(VALUE_GET) {
            this->value = value;
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
            for (auto a : args) {
                res.push_back((Tk)a);
            }
            return res;
        }
};


class LRop : public Expr {
    public:
        string op;
        LeftValue* left_value;
        // LRop() : Expr(LR_OP) {
        //     op = "";
        //     left_value = nullptr;
        // };
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
        Binop() : Expr(BINOP) {
            binop = "";
            v1 = nullptr;
            v2 = nullptr;
        };
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