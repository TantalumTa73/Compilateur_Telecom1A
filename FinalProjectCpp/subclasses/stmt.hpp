#pragma once
#include "../token.hpp"
#include "assembly.hpp"

class Stmt : public Token {
    public:
        Stmt(TokenType t ) : Token(t) {}
        virtual void print(string indent = "") override;
};


class Sscope : public Stmt {
    public:
        vector<Stmt*> body;
        Sscope() : Stmt(SCOPE){
            body = vector<Stmt*>();
        };
        Sscope(vector<Stmt*> body) : Stmt(SCOPE){
            this->body = body;
        };
        void print(string indent = "") override;

        unordered_map<string, Variable> vars;
        void init_var(string var_name, bool is_arg);
        vector<Tk> children() override {
            vector<Tk> res;
            for (auto v : body) {
                res.push_back((Tk) v);
            }
            return res;
        }

    private:
        int var_offset;
        int arg_offset;
};

class Sreturn : public Stmt {
    public:
        Expr* value;
        Sreturn() : Stmt(RETURN){
            value = nullptr;
        };
        Sreturn(Expr* value) : Stmt(RETURN){
            this->value = value;
        };
        void print(string indent = "") override;

        void on_exit() override;
        vector<Tk> children() override {
            return {(Tk)value};
        }
};

class Sfor : public Stmt {
    public:
        Stmt* init;
        Expr* condition;
        Stmt* increment;
        Stmt* body;
        Label* label_start ;
        Label* label_end ;
        Jz* goto_end ;
        Jmp* goto_start ;

        Sfor(Stmt* init, Expr* condition, Stmt* increment, Stmt* body, int label) : Stmt(FOR){
            this->init = init;
            this->condition = condition;
            this->increment = increment;
            this->body = body;
            this->label_start = new Label("L" + to_string(label) + "_start_for");
            this->label_end = new Label("L" + to_string(label) + "_end_for");
            this->goto_end = new Jz("L" + to_string(label) + "_end_for");
            this->goto_start = new Jmp("L" + to_string(label) + "_start_for");
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {
                (Tk)init, (Tk) label_start,
                (Tk)condition, (Tk) goto_end,
                (Tk)body, (Tk)increment, 
                (Tk) goto_start, (Tk) label_end
            };
        }
};

class Swhile : public Stmt {
    public:
        Expr* condition;
        Stmt* body;
        Label* label_start ;
        Label* label_end ;
        Jz* goto_end ;
        Jmp* goto_start ;
        Swhile(Expr* condition, Stmt* body, int label) : Stmt(WHILE){
            this->condition = condition;
            this->body = body;
            this->label_start = new Label("L" + to_string(label) + "_start_while");
            this->label_end = new Label("L" + to_string(label) + "_end_while");
            this->goto_end = new Jz("L" + to_string(label) + "_end_while");
            this->goto_start = new Jmp("L" + to_string(label) + "_start_while");
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {
                (Tk) label_start, 
                (Tk) condition, (Tk) goto_end,
                (Tk) body, (Tk) goto_start, (Tk) label_end
            };
        }
        // void on_enter() override;
};

class SvarDef : public Stmt {
    public:
        DataType type;
        string name;
        vector<int> array_size;
        Expr* value;
        // SvarDef() : Stmt(VAR_DEF){
        //     type = "";
        //     name = "";
        //     array_size = 0 ;
        //     value = nullptr;
        // };
        SvarDef(DataType type, string name, vector<int> array_size, Expr* value) : Stmt(VAR_DEF){
            this->type = type;
            this->name = name;
            this->array_size = array_size;
            this->value = value;
        };
        int get_size(){
            return 0 ;
            // return array_size * type_size(type);
        }
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children() override {
            if (value == nullptr) return {};
            return {(Tk)value};
        }
};

class SvarSet : public Stmt {
    public:
        LeftValue* left_value;
        string op;
        Expr* value;
        SvarSet() : Stmt(VAR_SET){
            left_value = nullptr;
            op = "";
            value = nullptr;
        };
        SvarSet(LeftValue* left_value, string op, Expr* value) : Stmt(VAR_SET){
            this->left_value = left_value;
            this->op = op;
            this->value = value;
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children() override {
            return {(Tk)left_value, (Tk)value};
        }
};

class Sexpr : public Stmt {
    public:
        Expr* value;
        Sexpr() : Stmt(EXPR_STMT){
            value = nullptr;
        };
        Sexpr(Expr* value) : Stmt(EXPR_STMT){
            this->value = value;
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)value};
        }
};

class Sif : public Stmt {
    public:
        Expr* condition;
        Stmt* body;
        Jz* goto_end ;
        Label* label_endif ;
        // Sif() : Stmt(IF){
        //     condition = nullptr;
        //     body = nullptr;
        // };
        Sif(Expr* condition, Stmt* body, int label) : Stmt(IF){
            this->condition = condition;
            this->body = body;
            this->goto_end = new Jz("L" + to_string(label) + "_endif");
            this->label_endif = new Label("L" + to_string(label) + "_endif");
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {(Tk)condition, (Tk) goto_end,(Tk) body, (Tk) label_endif};
        }
        void on_enter() override;
};

class SifElse : public Stmt {
    public:
        Expr* condition;
        Stmt* body_if;
        Stmt* body_else;
        Jz* goto_else ;
        Jmp* end_if ;
        Label* label_endif ;
        Label* label_else ;
        // Sif() : Stmt(IF){
        //     condition = nullptr;
        //     body = nullptr;
        // };
        SifElse(Expr* condition, Stmt* body_if, Stmt* body_else, int label) : Stmt(IF){
            this->condition = condition;
            this->body_if = body_if;
            this->body_else = body_else;
            this->goto_else = new Jz("L" + to_string(label) + "_else");
            this->label_else = new Label("L" + to_string(label) + "_else");
            this->end_if = new Jmp("L" + to_string(label) + "_endif");
            this->label_endif = new Label("L" + to_string(label) + "_endif");
        };
        void print(string indent = "") override;
        vector<Tk> children() override {
            return {
                (Tk) condition, (Tk) goto_else,
                (Tk) body_if, (Tk) end_if, 
                (Tk) label_else, (Tk) body_else,
                (Tk) label_endif
            };
        }
        void on_enter() override;
};

