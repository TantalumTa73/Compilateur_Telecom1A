#pragma once
#include "../token.hpp"
#include "assembly.hpp"
#include "expr.hpp"

class Stmt : public Token {
    public:
        Stmt(TokenType t ) : Token(t) {}
        virtual void print(string indent = "") override;
};


class Sscope : public Stmt {
    public:
        string name ;
        vector<Stmt*> body;
        string ctx ;
        Sscope() : Stmt(SCOPE){
            body = vector<Stmt*>();
        };
        Sscope(string name, vector<Stmt*> body, string ctx = "") : Stmt(SCOPE){
            this->name = name;
            this->body = body;
            this->ctx = ctx ;
        };

        void print(string indent = "") override;
        void on_enter() override ;
        void on_exit() override ;
        vector<Tk> children(string) override {
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
        vector<Tk> children(string) override {
            if (value == nullptr) return {};
            return {(Tk)value};
        }
};

class Skeyword : public Stmt {
    public:
        string keyword;
        Skeyword(string keyword) : Stmt(KEYWORD){
            this->keyword = keyword;
        };
        void print(string indent = "") override;
        void on_enter() override;
        vector<Tk> children(string label) override {
            if (keyword == "break"){
                v_cout << "break to " << label << endl;
                return {new Jmp(label)};
            } else if (keyword == "continue"){
                v_cout << "continue to " << label << endl;
                return {new Jmp(label)};
            } else {
                return {};
            }
        }
};

class Sfor : public Stmt {
    public:
        Stmt* init;
        Expr* condition;
        Stmt* update;
        Stmt* body;
        Label* label_start ;
        Label* label_update ;
        Label* label_end ;
        Jz* goto_end ;
        Jmp* goto_start ;

        Sfor(Stmt* init, Expr* condition, Stmt* update, Stmt* body, int label) : Stmt(FOR){
            this->init = init;
            this->condition = condition;
            this->update = update;
            this->body = body;
            this->label_start = new Label("L" + to_string(label) + "_start_for");
            this->label_update = new Label("L" + to_string(label) + "_update_for");
            this->label_end = new Label("L" + to_string(label) + "_end_for");
            this->goto_end = new Jz("L" + to_string(label) + "_end_for");
            this->goto_start = new Jmp("L" + to_string(label) + "_start_for");
        };
        void print(string indent = "") override;
        vector<Tk> children(string) override {
            return {
                (Tk) init, (Tk) label_start,
                (Tk) condition, (Tk) goto_end,
                (Tk) body, 
                (Tk) label_update, (Tk) update, 
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
        vector<Tk> children(string) override {
            return {
                (Tk) label_start, 
                (Tk) condition, (Tk) goto_end,
                (Tk) body, (Tk) goto_start, (Tk) label_end
            };
        }
};

class SvarDef : public Stmt {
    public:
        DataType type;
        string name;
        Expr* value;
        vector<int> ladder_size;
        SvarDef(DataType type, string name, Expr* value, vector<int> ladder_size) : Stmt(VAR_DEF){
            this->type = type;
            this->name = name;
            this->value = value;
            this->ladder_size.assign(ladder_size.begin(), ladder_size.end());
        };
        void print(string indent = "") override;
        void on_exit() override;
        vector<Tk> children(string) override {
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
        vector<Tk> children(string) override {
            if (
                value == nullptr ||
                // value->tk_type == LITTERAL_VOID ||
                // value->tk_type == LITTERAL_INT ||
                // value->tk_type == LITTERAL_BOOL ||
                // value->tk_type == LITTERAL_CHAR ||
                value->tk_type == LITTERAL_STRING
            ) return {(Tk)left_value};
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
        vector<Tk> children(string) override {
            return {(Tk)value};
        }
};

class Sif : public Stmt {
    public:
        Expr* condition;
        Stmt* body;
        Jz* goto_end ;
        Label* label_endif ;
        Sif(Expr* condition, Stmt* body, int label) : Stmt(IF){
            this->condition = condition;
            this->body = body;
            this->goto_end = new Jz("L" + to_string(label) + "_endif");
            this->label_endif = new Label("L" + to_string(label) + "_endif");
        };
        void print(string indent = "") override;
        vector<Tk> children(string) override {
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
        vector<Tk> children(string) override {
            return {
                (Tk) condition, (Tk) goto_else,
                (Tk) body_if, (Tk) end_if, 
                (Tk) label_else, (Tk) body_else,
                (Tk) label_endif
            };
        }
        void on_enter() override;
};

