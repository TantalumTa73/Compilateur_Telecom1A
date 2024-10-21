#include "json_reader.hpp"

Token* JsonReader::to_token(RawToken raw_token){
    if (raw_token.get_attribute("action") == "root"){
        Token* token = new UndefinedToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    } 
    if (raw_token.get_attribute("action") == "return"){
        Token* token = new ReturnToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("action") == "gvardef"){
        Token* token = new DefVarToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("action") == "gfundef"){
        std::vector<std::string> arg_names = std::vector<std::string>();
        if (raw_token.get_attribute("arg") != ""){
            arg_names.push_back(raw_token.get_attribute("arg"));
        }
        Token* token = new DefFunToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char, arg_names); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("action") == "function"){
        Token* token = new CallFunToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("action") == "varset"){
        Token* token = new SetVarToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("type") == "var"){
        Token* token = new GetVarToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("type") == "cst"){
        Token* token = new CstToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char,
        raw_token.end_line, raw_token.end_char, std::stoi(raw_token.get_attribute("value"))); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("operator") != ""){
        Token* token = new OpToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char, raw_token.get_attribute("operator")); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }
    if (raw_token.get_attribute("type") == "parenthesis"){
        Token* token = new ParenthesisToken(raw_token.get_attribute("name"), raw_token.start_line, raw_token.start_char, raw_token.end_line, raw_token.end_char); 
        for (auto child : raw_token.children){
            token->add_child(to_token(child));
        }
        return token;
    }

    return new UndefinedToken("", 0, 0, -1, -1);
}

Token* JsonReader::readFile(){

    std::ifstream file = std::ifstream(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return new UndefinedToken("", 0, 0, -1, -1);
    }

    RawToken root = RawToken("", 0, 0, -1, -1);
    root.set_attribute("action", "root");
    RawToken *token_ptr = &root;

    // v_cout << "Main at " << token_ptr << "\n";
    
    std::string name ;
    std::string value ;
    bool is_name ;
    char c ;
        
    while ( ! file.eof() ) {
        c = file.get();
        
        if (c == '{'){
            token_ptr->add_child(RawToken());
            token_ptr = &token_ptr->children.back();
            name = "" ;
            value = "" ;
            is_name = true ;
            // v_cout << "New object at " << token_ptr << ", parent: " << token_ptr->parent << "\n";
        }
        else if (c == ',' || c == '}'){
            // v_cout << "Adding to " << token_ptr << " : " << name << " : " << value << "\n";
            
            if (value != "")
                token_ptr->set_attribute(name, value);

            name = "";
            value = "";
            is_name = true;
            
            if (c == '}'){
                token_ptr = token_ptr->parent;
            }
        }
        else if (c == ':' && is_name) {
            is_name = false;
        }
        else if (c == ':' && ! is_name) {
            std::cerr << "Error in file: " << filename << "\n";
            
            break;
        }
        else if (c != '\n' && c != '\t' && c != '\"' && c != ' '){
            if (is_name) name += c;
            else value += c;
        }        
    }

    file.close();

    // v_cout << "End at object : " << token_ptr << " (" << (token_ptr==&root)<< ")\n";


    return to_token(root);
}

