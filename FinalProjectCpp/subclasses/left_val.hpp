#pragma once
#include "../token.hpp"

class LeftValue : public Token {
    public:
        LeftValue(TokenType t) : Token(t) {};
        void print(string indent = "") override ;
        // virtual string get_id() = 0;
        virtual string get_address() = 0;
};

class VarGet : public LeftValue {
    public:
        string name;
        // VarGet() : LeftValue(VAR_GET) {
        //     name = "";
        // };
        VarGet(string name) : LeftValue(VAR_GET) {
            this->name = name;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {};
        }
        string get_address() override {
            Variable variable = find_var(name);
            return variable.get_adress();
        }
        
};

class ArrayGet : public LeftValue {
    public:
        LeftValue* left_value;
        Expr* index;
        ArrayGet() : LeftValue(ARRAY_GET) {
            left_value = nullptr;
            index = nullptr;
        };
        ArrayGet(LeftValue* left_value, Expr* index) : LeftValue(ARRAY_GET) {
            this->left_value = left_value;
            this->index = index;
            // ERROR("ArrayGet not implemented");
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)left_value, (Tk)index};
        }
        string get_address() override {
            ERROR("ArrayGet not implemented");
            string name ;
            //  = left_value->get_address() + "[" + "]";
            Variable variable = find_var(name);
            return variable.get_adress();
        }
};

class LeftValOp : public LeftValue {
    public:
        LeftValue* left_value;
        string op;
        LeftValOp() : LeftValue(LEFT_VAL_OP) {
            left_value = nullptr;
            op = "";
        };
        LeftValOp(LeftValue* left_value, string op) : LeftValue(LEFT_VAL_OP) {
            this->left_value = left_value;
            this->op = op;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)left_value};
        }
        void on_exit() override;
        string get_address() override {
            ERROR("LeftValOp not implemented");
            string name = left_value->get_address() ;
            Variable variable = find_var(name);
            return variable.get_adress();
        }
};