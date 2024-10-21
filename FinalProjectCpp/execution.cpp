#include "execution.hpp"

Execution::Execution(Root* tk){

    for (GStmt* gstmt : tk->gstmts){
        if (gstmt->tk_type == G_VAR_DEF){
            GVarDef* gvardef = dynamic_cast<GVarDef*>(gstmt);
            gvars.push_back(gvardef);
        } else if (gstmt->tk_type == G_FUN_DEF){
            GFunDef* gfundef = dynamic_cast<GFunDef*>(gstmt);
            funcs.push_back(gfundef);
        } else {
            ERROR("Unknown GStmt type \n");
        }
    }

    for (GVarDef* gvar : gvars){
        v_cout << "VarDef: " << gvar->name << "\n";
    }
    for (GFunDef* gfun : funcs){
        v_cout << "FunDef: " << gfun->name << "\n";
    }

}