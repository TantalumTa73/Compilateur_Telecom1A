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

class LLop : public LeftValue {
    public:
        LeftValue* left_value;
        string op;
        // LLop() : LeftValue(LL_OP) {
        //     left_value = nullptr;
        //     op = "";
        // };
        LLop(LeftValue* left_value, string op) : LeftValue(LL_OP) {
            this->left_value = left_value;
            this->op = op;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)left_value};
        }
        string get_address() override {
            ERROR("LLop not implemented");
            string name ;
            //  = left_value->get_address() + "[" + "]";
            Variable variable = find_var(name);
            return variable.get_adress();
        }
};

class RLop : public LeftValue {
    public:
        string op;
        Expr* value;
        // RLop() : LeftValue(RL_OP) {
        //     op = "";
        //     value = nullptr;
        // };
        RLop(string op, Expr* value) : LeftValue(RL_OP) {
            this->op = op;
            this->value = value;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)value};
        }
        string get_address() override {
            ERROR("RLop not implemented");
            string name ;
            //  = left_value->get_address() + "[" + "]";
            Variable variable = find_var(name);
            return variable.get_adress();
        }
};