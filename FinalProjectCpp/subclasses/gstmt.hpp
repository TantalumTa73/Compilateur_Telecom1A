
#include "../token.hpp"

class GStmt : public Token {
    public:
        GStmt();
        GStmt(JSON* json);
        virtual void print() override;
};

class GFunDef : public GStmt {
    public:
        string name;
        string type;
        vector<Arg*> args;
        Stmt* body;
        GFunDef();
        GFunDef(JSON* json);
        void print() override;
};

class GVarDef : public GStmt {
    public:
        string name;
        string type;
        GVarDef();
        GVarDef(JSON* json);
        void print() override;
};