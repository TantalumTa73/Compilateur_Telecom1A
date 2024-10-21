#include <vector>
#include <string>
#include <algorithm>

#include "token.hpp"
#include "simplified_token.hpp"
#include "exception.hpp"


TkPtr simplify(Token token){

    if        (token.get_attribute("name") == "__root__"){
        return new FunctionDef(token, "__root__", "__arg__", simplify(token.children));

    } else if (token.get_attribute("action") == "gfundef"){
        return new FunctionDef(token, token.get_attribute("name"), 
            token.get_attribute("arg"), simplify(token.children));

    } else if (token.get_attribute("action") == "gvardef"){
        return new VarDef(token, token.get_attribute("name"));

    } else if (token.get_attribute("action") == "varset"){
        return new VarSet(token, token.get_attribute("name"));

    } else if (token.get_attribute("action") == "function"){
        return new FunctionCall(token, token.get_attribute("name"), "");

    } else if (token.get_attribute("type") == "var"){
        return new VarGet(token, token.get_attribute("name"));

    } else if (token.get_attribute("type") == "cst"){
        return new Constant(token, std::stoi(token.get_attribute("value")));

    } else if (token.get_attribute("type") == "operation"){
        int nb_arg = token.get_attribute("operator") == "uminus" ? 1 : 2;
        return new Operator(token, token.get_attribute("operator"), nb_arg);

    } else if (token.get_attribute("action") == "return"){
        return new Return(token);
    }

    token.print();

    throw InterpreterException(token, 
        "Unknown action (simplify) [" + token.get_attribute("action")
        + ", " + token.get_attribute("type") + "]"
    );
    return nullptr;
}

std::vector<TkPtr> simplify(std::vector<Token> tokens){

    std::vector<TkPtr> new_tokens = std::vector<TkPtr>();
    reverse(tokens.begin(), tokens.end()) ;
   

    while (tokens.size() > 0){
        Token t = tokens.back();
        tokens.pop_back();

        if (
            t.get_attribute("action") != "gfundef" &&
            t.get_attribute("action") != "gvardef" &&
            t.childs.size() > 0 &&
            t.get_attribute("name") != "__root__"
        ){
            std::vector<Token> childs = t.childs;
            t.childs = std::vector<Token>();
            tokens.push_back(t);
            for (Token child : childs) tokens.push_back(child) ;
    
        } else if (t.get_attribute("type")=="parenthesis"){
            // parenthesis are ignored    
        } else {
            new_tokens.push_back(simplify(t));
        }
    }


    return new_tokens;
}