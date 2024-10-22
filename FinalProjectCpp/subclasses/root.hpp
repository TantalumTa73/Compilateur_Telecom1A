#pragma once
#include "../token.hpp"

class Root : public Token {
    public:
        vector<GStmt*> gstmts;
        Root() : Token(ROOT) {
            gstmts = vector<GStmt*>();
        }
        Root(vector<GStmt*> gstmts) : Token(ROOT) {
            this->gstmts = gstmts;
        }
        void print(string indent = ""){
            v_cout << indent << "Root" << endl;
            for(auto v : gstmts){
                v->print(indent + "  ");
            }
        }
        vector<Tk> children() {
            vector<Tk> res;
            for(auto v : gstmts){
                res.push_back(v);
            }
            return res;
        }
};