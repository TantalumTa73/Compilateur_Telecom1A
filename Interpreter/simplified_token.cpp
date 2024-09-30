#include <vector>
#include <string>

#include "token.hpp"
#include "json_simplifier.hpp"

Token simplify(Token token){
    Token new_token = Token(token.start_line, token.start_char, token.end_line, token.end_char);

    new_token.childs = simplify(token.childs) ;

    for (auto const& [key, val] : token.attributes){
        new_token.set_attribute(key, val);
    }

    return new_token;
}

std::vector<Token> simplify(std::vector<Token> tokens){

    std::vector<Token> new_tokens = std::vector<Token>();
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