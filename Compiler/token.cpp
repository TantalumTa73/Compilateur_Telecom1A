#include "token.hpp"
#include "write_assembly.hpp"

std::unordered_map<std::string, Function> functions = std::unordered_map<std::string, Function>();
std::vector<std::string> called_fun_names = std::vector<std::string>();
bool verbose = false;


// Raw Token --------------------------------------------------------------------------------------------------------------------------------
RawToken::RawToken(){
    start_line = 0;
    start_char = 0;
    end_line = 0;
    end_char = 0;
    parent = nullptr;
    children = std::vector<RawToken>();
}

RawToken::RawToken(std::string name, int start_line, int start_char, int end_line, int end_char){
    start_line = 0;
    start_char = 0;
    end_line = 0;
    end_char = 0;
    parent = nullptr;
    children = std::vector<RawToken>();
}

std::string RawToken::get_attribute(std::string key) {
    auto it = attributes.find(key);
    if (it != attributes.end()) {
        return it->second;
    }
    return "";
}

void RawToken::set_attribute(std::string key, std::string value) {
    if      (key == "start_line") start_line = std::stoi(value);
    else if (key == "start_char") start_char = std::stoi(value);
    else if (key == "end_line") end_line = std::stoi(value);
    else if (key == "end_char") end_char = std::stoi(value);
    else attributes[key] = value;
    
    return ;
}

void RawToken::add_child(RawToken child){
    child.parent = this;
    children.push_back(child);
    return ;
}


// Token --------------------------------------------------------------------------------------------------------------------------------
Token::Token(){
    start_line = 0;
    start_char = 0;
    end_line = 0;
    end_char = 0;
    id = UNDEFINED;
    name = "";
    parent = nullptr;
    children = std::vector<Token*>();
}

Token::Token
(std::string name_, int start_line_, int start_char_, int end_line_, int end_char_, TokenType id_){
    start_line = start_line_;
    start_char = start_char_;
    end_line = end_line_;
    end_char = end_char_;
    id = id_;
    name = name_; 
    parent = nullptr;
    children = std::vector<Token*>();
}

void Token::add_child(Token* child){
    child->parent = this;
    children.push_back(child);
    return ;
}

Variable Token::find_var(std::string var_name){
    std::cout << "----------entering in find_var\n";
    std::cout << "  called_fun_names' size : " << std::to_string(called_fun_names.size()) << "\n"; 
    // to begin with the last called section
    reverse(called_fun_names.begin(), called_fun_names.end());
    for (auto fun_name : called_fun_names){
        if (functions[fun_name].vars.find(var_name) != functions[fun_name].vars.end()){
            std::cout << "  " << var_name << "'s offset : " << std::to_string(functions[fun_name].vars[var_name].offset) << " in (compiler.cpp)\n";
            return functions[fun_name].vars[var_name];
        }
    }
    reverse(called_fun_names.begin(), called_fun_names.end());

    std::cout << "  " << var_name << " not found (compiler.cpp)\n";
    return Variable();
}

// RETURN --------------------------------------------------------------------------------------------------------------------------------
ReturnToken::ReturnToken(std::string name, int start_line, int start_char, int end_line, int end_char) 
: Token(name, start_line, start_char, end_line, end_char, RETURN) {}

void ReturnToken::on_enter(){
    std::cout << "----- entering in CallFunToken ------\n";
}

void ReturnToken::after_all_children_processed(){
    w_ret(called_fun_names.back() == MAIN);
    std::cout << "----- leaving from CallFunToken ------\n";
}


// DEF_VAR --------------------------------------------------------------------------------------------------------------------------------
DefVarToken::DefVarToken(std::string name, int start_line, int start_char, int end_line, int end_char) 
: Token(name, start_line, start_char, end_line, end_char, DEF_VAR) {}

void DefVarToken::on_enter() {}

void DefVarToken::after_all_children_processed(){
    functions[called_fun_names.back()].init_var(name, false);
    if (called_fun_names.back() == GLOBAL){
        w_init_global_var(name);
    } else {
        w_init_var();
    }
}


// DEF_FUNCTION --------------------------------------------------------------------------------------------------------------------------------
DefFunToken::DefFunToken(std::string name, int start_line, int start_char, int end_line, int end_char, std::vector<std::string> arg_names) 
: Token(name, start_line, start_char, end_line, end_char, DEF_FUN) {
    this->arg_names = arg_names;
}

void DefFunToken::on_enter(){
    std::cout << "----- entering in DefFunToken ------\n";
    Function f = Function(name);
    functions.insert({name, f});

    called_fun_names.push_back(name);

    if (name == GLOBAL) { return; }

    w_init_f(name);

    for (std::string arg_name : arg_names){
        functions[name].init_var(arg_name, true);
    }
}

void DefFunToken::after_all_children_processed(){
    // avoid a function that doesn't have return
    w_ret(called_fun_names.back() == MAIN);
    std::cout << "----- leaving from DefFunToken ------\n";
}


// CALL_FUN --------------------------------------------------------------------------------------------------------------------------------
CallFunToken::CallFunToken(std::string name, int start_line, int start_char, int end_line, int end_char) 
: Token(name, start_line, start_char, end_line, end_char, CALL_FUN) {}

void CallFunToken::on_enter(){
    std::cout << "----- entering in CallFunToken ------\n";
    if (auto search = functions.find(name); search == functions.end()){
        std::cout << name << " unknown in functions";
        return;
    }
}

void CallFunToken::after_all_children_processed(){
    w_call_function(name);
    std::cout << "----- leaving from CallFunToken ------\n";
}


// SET_VAR --------------------------------------------------------------------------------------------------------------------------------
SetVarToken::SetVarToken(std::string name, int start_line, int start_char, int end_line, int end_char) 
: Token(name, start_line, start_char, end_line, end_char, SET_VAR) {}

void SetVarToken::on_enter(){
    std::cout << "----- entering in SetVarToken ------\n";
}

void SetVarToken::after_all_children_processed(){
    Variable variable_buffer = find_var(name);
    std::cout << variable_buffer.name << "'s function is : " << variable_buffer.fun_name << "\n";
    if (variable_buffer.fun_name == GLOBAL){
        w_set_global_var(variable_buffer.name);
    } else {
        std::cout << "  " << variable_buffer.name << "'s offset : " << variable_buffer.offset << "\n";
        w_set_var(variable_buffer.offset);
    }
    std::cout << "----- leaving from SetVarToken ------\n";
}


// GET_VAR --------------------------------------------------------------------------------------------------------------------------------
GetVarToken::GetVarToken(std::string name, int start_line, int start_char, int end_line, int end_char) 
: Token(name, start_line, start_char, end_line, end_char, GET_VAR) {}

void GetVarToken::on_enter() {
    std::cout << "----- entering in GetVarToken ------\n";
}

void GetVarToken::after_all_children_processed(){
    Variable variable_buffer = find_var(name);
    if (variable_buffer.fun_name == GLOBAL){
        w_push_global_var(name);
    } else {
        w_push_local_var(variable_buffer.offset);
    }
    std::cout << "----- leaving from GetVarToken ------\n";
}


// CST --------------------------------------------------------------------------------------------------------------------------------
CstToken::CstToken(std::string name, int start_line, int start_char, int end_line, int end_char, int value) 
: Token(name, start_line, start_char, end_line, end_char, CST){
    this->value = value;
}

void CstToken::on_enter(){
    w_push_cst(value);
}

void CstToken::after_all_children_processed() {}


// OP --------------------------------------------------------------------------------------------------------------------------------
OpToken::OpToken(std::string name, int start_line, int start_char, int end_line, int end_char, std::string op_name) 
: Token(name, start_line, start_char, end_line, end_char, OP){
    this->op_name = op_name;
}

void OpToken::on_enter(){
    std::cout << "----- entering in OpToken ------\n";
}

void OpToken::after_all_children_processed(){
    w_op(op_name);
    std::cout << "----- leaving from OpToken ------\n";
}


// PARENTHESIS --------------------------------------------------------------------------------------------------------------------------------
ParenthesisToken::ParenthesisToken(std::string name, int start_line, int start_char, int end_line, int end_char) 
: Token(name, start_line, start_char, end_line, end_char, PARENTHESIS) {}

void ParenthesisToken::on_enter() {}

void ParenthesisToken::after_all_children_processed() {}


// PARENTHESIS --------------------------------------------------------------------------------------------------------------------------------
UndefinedToken::UndefinedToken(std::string name, int start_line, int start_char, int end_line, int end_char) 
: Token(name, start_line, start_char, end_line, end_char, PARENTHESIS) {}

void UndefinedToken::on_enter() {}

void UndefinedToken::after_all_children_processed() {}