#pragma once
#include <string>
#include <vector>

#include "token.hpp"

#include "subclasses/arg.hpp"
#include "subclasses/expr.hpp"
#include "subclasses/gstmt.hpp"
#include "subclasses/left_val.hpp"
#include "subclasses/litteral.hpp"
#include "subclasses/root.hpp"
#include "subclasses/stmt.hpp"

class Execution {
    public:
        Execution(){}
        Execution(Root* tk);
        // void run();

    private:
        vector<GVarDef*> gvars;
        vector<GFunDef*> funcs;

        // vector<Stmt*> tk_stack ;
        // vector<Stmt*> calc_stack ;
};