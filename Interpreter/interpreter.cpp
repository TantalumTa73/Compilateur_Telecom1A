#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <assert.h>

#include "simplified_token.hpp"
#include "interpreter.hpp"
#include "exception.hpp"
#include "functions.hpp"


Interpreter::Interpreter() {

    functions = std::unordered_map<std::string, Function>();

    stack = std::vector<TkPtr>();
    stack_context = std::vector<std::string>();

    value_stack = std::vector<int>();

    return;
}

Interpreter::Interpreter(TkPtr root_) {
    

    if (root_->type != FUNCTION_DEF){
        throw InterpreterException(root_, "Root is not a function (type)");
    } else if (root_ == nullptr){
        throw InterpreterException(root_, "Root is not a function (ptr)");
    }
    FunctionDef root_tk = dynamic_cast<FunctionDef&>(*root_);

    v_cout << std::endl;

    stack = root_tk.body;
    reverse(stack.begin(), stack.end()) ;
    root_tk.body = std::vector<TkPtr>();

    functions = std::unordered_map<std::string, Function>();
    Function root = Function(root_tk);
    functions.insert(std::make_pair("__root__", root));


    stack_context = std::vector<std::string>();
    for (uint i = 0 ; i < stack.size() ; i++){
        stack_context.push_back("__root__");
    }

    value_stack = std::vector<int>();

    return;
}


void Interpreter::push(int value){
    value_stack.push_back(value);
    return ;
}

int Interpreter::pop(){

    if (value_stack.size() == 0){
        throw InterpreterException(actual_token, "No value to pop");
    }
    int value = value_stack.back();
    value_stack.pop_back();
    return value;
}


void Interpreter::get_var(VarGet token){

    if (
        functions.find(actual_function) != functions.end() && 
        functions[actual_function].get_var(token.var_name).has_value()
    ){
        v_cout << "Get variable " << token.var_name ;
        v_cout << " in " << actual_function ;

        int value = functions[actual_function].get_var(token.var_name).value();

        v_cout << " (=" << value << ")" << std::endl;

        push(value);
        return ;

    } else if (functions["__root__"].get_var(token.var_name).has_value()){

        v_cout << "Get variable " << token.var_name ;
        v_cout << " in " << "__root__" ;

        int value = functions["__root__"].get_var(token.var_name).value();

        v_cout << " (=" << value << ")" << std::endl;

        push(value);
        return ;

    } else {
        std::string msg = "Variable " + token.var_name + " not found (get_var)";
        throw InterpreterException(actual_token, msg);
    }
    
    return ;

}

void Interpreter::set_var(VarSet token){

    int value = pop();
    v_cout << "Set variable " << token.var_name << " to " << value ;
    v_cout << " in " << actual_function << std::endl;

    if (
        functions.find(actual_function) != functions.end() && 
        functions[actual_function].get_var(token.var_name).has_value()
    ){
        
        functions[actual_function].set_var(token.var_name, value);

    } else if (functions["__root__"].get_var(token.var_name).has_value()){

        v_cout << " in __root__" << std::endl;
        functions["__root__"].set_var(token.var_name, value);

    } else {
        std::string msg = "Variable " + token.var_name + " not found (set_var)";
        throw InterpreterException(actual_token, msg);
    }
    
    return ;
}

void Interpreter::def_var(VarDef token){

    if (functions.find(actual_function) != functions.end()){
        v_cout << "Def variable " << token.var_name ;
        v_cout << " in " << actual_function << std::endl;
        functions[actual_function].set_var(token.var_name, 0);

    } else {
        std::string msg = "Function " + actual_function + " not found (def_var)";
        throw InterpreterException(actual_token, msg);
    }

    

    return ;
}

void Interpreter::get_value(Operator token){

    std::string op = token.operator_name;

    if (token.nb_args == 1){
        int left_value = pop();
        if (op == "uminus") return push(-left_value) ;

        throw InterpreterException(&token, "Unknown 1-operator " + op);

    } else if (token.nb_args == 2){
        int left_value = pop();
        int right_value = pop();
        v_cout << "Operation " << left_value << " " << op << " " << right_value << std::endl;
        token.print();

        if (op == "mult") return push(left_value * right_value);
        if (op == "division") return push(left_value / right_value);
        if (op == "modulo") return push(left_value % right_value);
        if (op == "plus") return push(left_value + right_value);
        if (op == "minus") return push(left_value - right_value);

        throw InterpreterException(&token, "Unknown 2-operator " + op);

    } else {

        throw InterpreterException(&token, "Unknown operator " + op);
    }
}

void Interpreter::get_value(Constant token){
    v_cout << "Constant " << token.value << std::endl;
    push(token.value);
    return ;
}

void Interpreter::get_value(Return token){
    int value = pop();
    v_cout << "Return " << value << " in " << actual_function ;
    v_cout << " (" << token.start_line << "," << token.start_char << ")";
    v_cout << std::endl;
    push(value);
    return ;
}

void Interpreter::def_function(FunctionDef token){
    
    v_cout << "Defining function " << token.fun_name << "\n";

    Function f = Function(token);
    functions.insert(std::make_pair(token.fun_name, f));

    return ;
}

void Interpreter::call_function(FunctionCall token){
    
    int arg = pop();

    v_cout << "Calling function " << token.name ;
    v_cout << " in " << actual_function << " with arg " << arg << std::endl;

    if (token.name == "__root__"){
        std::string msg = "Cannot call __root__ function (call_function)";
        throw InterpreterException(-2,-2,-2,-2, msg);
    } else if (token.name == "print"){
        v_cout << "Printing " << arg << std::endl;
        std::cout << arg << std::endl;
    } else if (token.name == "input" || token.name == "read"){
        v_cout << "Need Input for " << arg << std::endl;
        v_cout << "\'read\' not implemented yet\n";
        
        int input;
        std::cin >> input;
        push(input);
        // set_var(VarSet(Token(0,0,0,0), ""));

        v_cout << "Input: " << input << std::endl;

    } else if (functions.find(token.name) != functions.end()){
        
        
        Function& f = functions[token.name];
        f.set_var(f.arg_name, arg); 

        reverse(f.body.begin(), f.body.end()) ;
        for (TkPtr t : f.body){
            stack.push_back(t);
            stack_context.push_back(token.name);
        }
        reverse(f.body.begin(), f.body.end()) ;

    } else {
        std::string msg = "Function " + token.name + " not found (call_function)";
        throw InterpreterException(-2,-2,-2,-2, msg);
    }

}


void Interpreter::run() {

    v_cout << "Running interpreter\n" ;
    v_cout << "Nb tokens: " << stack.size() << "\n\n";

    bool defining = true ;

    v_cout << "Printing\n";
    reverse(stack.begin(), stack.end()) ;
    for (auto t : stack) t->print();
    reverse(stack.begin(), stack.end()) ;

    v_cout << "\nDefining\n";

    while (true) {
        actual_token = stack.back();
        actual_function = stack_context.back();
        stack.pop_back();
        stack_context.pop_back();

        
        if (actual_token->type == VAR_DEF) {
            VarDef *tk = static_cast<VarDef*>(actual_token);
            assert(tk != nullptr);
            def_var(*tk);

        } else if (actual_token->type == FUNCTION_DEF) {
            FunctionDef *tk = static_cast<FunctionDef*>(actual_token);
            assert(tk != nullptr);
            def_function(*tk);

        } else if (actual_token->type == VAR_SET) {
            VarSet *tk = static_cast<VarSet*>(actual_token);
            assert(tk != nullptr);
            set_var(*tk);
            
        } else if (actual_token->type == FUNCTION_CALL) {
            FunctionCall *tk = static_cast<FunctionCall*>(actual_token);
            assert(tk != nullptr);
            call_function(*tk);

        } else if (actual_token->type == CONSTANT) {
            Constant *tk = static_cast<Constant*>(actual_token);
            assert(tk != nullptr);
            get_value(*tk);

        } else if (actual_token->type == VAR_GET) {
            VarGet *tk = static_cast<VarGet*>(actual_token);
            assert(tk != nullptr);
            get_var(*tk);

        } else if (actual_token->type == OPERATOR) {
            Operator *tk = static_cast<Operator*>(actual_token);
            assert(tk != nullptr);
            get_value(*tk);

        } else if (actual_token->type == RETURN) {
            Return *tk = static_cast<Return*>(actual_token);
            assert(tk != nullptr);
            get_value(*tk);
            
        } else {
            v_cout << "Unknown action: " << actual_token->type << std::endl;
            throw InterpreterException(actual_token, "Unknown action (run)");
        }

        if (stack.size() == 0 && defining) {
            v_cout << "\nExecuting\n";
            push(0);
            FunctionCall main = FunctionCall(Token(0,0,0,0), "main", "arg");
            call_function(main);
            defining = false;
        } else if (stack.size() == 0){
            break;
        }


    }

    return ;
}














