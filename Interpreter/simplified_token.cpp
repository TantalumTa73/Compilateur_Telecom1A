#include <vector>
#include <string>

#include "token.hpp"
#include "simplified_token.hpp"
#include "exception.hpp"

SimplifiedToken simplify(Token token){
    // SimplifiedToken new_token ;

    if (token.get_attribute("action") == "gfundef"){
        return FunctionDef(token, token.get_attribute("name"), token.get_attribute("arg"), simplify(token.childs));
    } else if (token.get_attribute("action") == "gvardef"){
        return VarDef(token, token.get_attribute("name"));
    } else if (token.get_attribute("action") == "varset"){
        return VarSet(token, token.get_attribute("name"));
    } else if (token.get_attribute("action") == "function"){
        return FunctionCall(token, token.get_attribute("name"), token.childs[0].get_attribute("name"));
    } else if (token.get_attribute("action") == "calc"){
        return Calc(token, token.get_attribute("type"), token.childs.size());
    } else if (token.get_attribute("action") == "return"){
        return Return(token);
    }

    throw InterpreterException(token, "Unknown action");
}

std::vector<SimplifiedToken> simplify(std::vector<Token> tokens){

    std::vector<SimplifiedToken> new_tokens = std::vector<SimplifiedToken>();
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
            for (Token child : childs){
                if (child.get_attribute("action") == "")
                    child.set_attribute("action", "calc");
                tokens.push_back(child);
            }
    
        } else if (t.get_attribute("type")=="parenthesis"){        
        } else {
            new_tokens.push_back(simplify(t));
        }

    }

    

    return new_tokens;
}