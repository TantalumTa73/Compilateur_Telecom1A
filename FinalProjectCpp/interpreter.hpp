#pragma once
#include <string>
#include <vector>

#include "token.hpp"
#include "subclasses/gstmt.hpp"

class Interpreter {
    public:
        Interpreter();
        Interpreter(Tk tk);
        void run();

    private:
        vector<GVarDef*> gvars;
        vector<GFunDef*> funcs;

        vector<Stmt*> tk_stack ;
        vector<Stmt*> calc_stack ;
};