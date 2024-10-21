#pragma once
#include "../token.hpp"

class Root : public Token {
    public:
        vector<GStmt*> gstmts;
        Root(){
            gstmts = vector<GStmt*>();
        }
        Root(vector<GStmt*> gstmts){
            this->gstmts = gstmts;
        }
        void print(string indent = ""){
            cout << indent << "Root" << endl;
            for(auto v : gstmts){
                v->print(indent + "  ");
            }
        }
};