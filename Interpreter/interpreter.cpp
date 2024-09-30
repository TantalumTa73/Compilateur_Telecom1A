#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>

#include "token.hpp"
#include "interpreter.hpp"
#include "exception.hpp"
#include "functions.hpp"


Interpreter::Interpreter() {
    gvar = std::unordered_map<std::string, int>();
    functions = std::unordered_map<std::string, Function>();

    stack = std::vector<Token>();
    stack_context = std::vector<std::string>();

    return;
}

Interpreter::Interpreter(Token root) {
    gvar = std::unordered_map<std::string, int>();
    functions = std::unordered_map<std::string, Function>();

    reverse(root.childs.begin(), root.childs.end()) ;    
    for (Token t : root.childs){
        stack.push_back(t);
        stack_context.push_back("__root__");
    }
    reverse(root.childs.begin(), root.childs.end()) ;

    return;
}


int Interpreter::get_var(std::string var_name){

    if (
        functions.find(actual_function) != functions.end() && 
        functions[actual_function].get_var(var_name).has_value() && 
        actual_function != "__root__"
    ){
        v_cout << "Get local variable " << var_name ;
        v_cout << " in " << actual_function << std::endl;

        return functions[actual_function].get_var(var_name).value();

    } else if (gvar.find(var_name) != gvar.end()){

        v_cout << "Get global variable " << var_name ;
        v_cout << " (func " << actual_function << ")" << std::endl;
        return gvar[var_name] ;

    } else {
        std::string msg = "Variable " + var_name + " not found (get_var)";
        throw InterpreterException(actual_token, msg);
    }
    
    return -1;

}

void Interpreter::set_var(std::string var_name, int value){

    if (
        functions.find(actual_function) != functions.end() && 
        functions[actual_function].get_var(var_name).has_value() && 
        actual_function != "__root__"
    ){

        v_cout << "Set local variable " << var_name << " to " << value ;
        v_cout << " in " << actual_function << std::endl;
        functions[actual_function].set_var(var_name, value);

    } else if (gvar.find(var_name) != gvar.end()){

        v_cout << "Set global variable " << var_name << " to " << value ;
        v_cout << " (func " << actual_function << ")" << std::endl;
        gvar[var_name] = value;

    } else {
        std::string msg = "Variable " + var_name + " not found (set_var)";
        throw InterpreterException(actual_token, msg);
    }
    
    return ;
}

void Interpreter::def_var(std::string var_name){

    if (actual_function == "__root__"){

        v_cout << "Def global variable " << var_name ;
        v_cout << " (func " << actual_function << ")" << std::endl;
        gvar[var_name] = 0;

    } else if (functions.find(actual_function) != functions.end()){
        v_cout << "Def local variable " << var_name ;
        v_cout << " in " << actual_function << std::endl;
        functions[actual_function].set_var(var_name, 0);

    } else {
        std::string msg = "Function " + actual_function + " not found (def_var)";
        throw InterpreterException(actual_token, msg);
    }

    

    return ;
}

int Interpreter::get_value(Token token){


    if (token.get_attribute("type") == "cst"){
        // v_cout << "\t Constant\n" ;
        return std::stoi(token.get_attribute("value"));

    } else if (token.get_attribute("type") == "var"){
        // v_cout << "\t Variable\n" ;
        return get_var(token.get_attribute("name"));

    } else if (token.get_attribute("type") == "operation"){
        // v_cout << "\t Operation\n" ;

        Token left = token.childs[0];
        int left_value = get_value(left);

        std::string op = token.get_attribute("operator");

        if (op == "uminus") return -left_value ;

        Token right = token.childs[1];
        int right_value = get_value(right);

        v_cout << "Operation " << left_value << " " << op << " " << right_value << std::endl;

        if (op == "mult") return left_value * right_value;
        if (op == "division") return left_value / right_value;
        if (op == "modulo") return left_value % right_value;
        if (op == "plus") return left_value + right_value;
        if (op == "minus") return left_value - right_value;
        
        throw InterpreterException(token, "Unknown operator " + op);

    } else if (token.get_attribute("type")=="parenthesis"){
        // v_cout << "\t Parenthesis\n" ;
        return get_value(token.childs[0]);

    } else if (token.get_attribute("action") == "function"){
        // v_cout << "\t Function\n" ;
        std::string fun_name = token.get_attribute("name");
        int arg = get_value(token.childs[0]);
        call_function(fun_name, arg);
        return last_value;

    } else {
        v_cout << "\t Unknown :" << token.get_attribute("type") << std::endl;
    }

    return -1;
}

void Interpreter::call_function(std::string fun_name, int arg){
    
    v_cout << "Calling function " << fun_name ;
    v_cout << " in " << actual_function << " with arg " << arg << std::endl;

    if (fun_name == "print"){
        v_cout << "Printing " << arg << std::endl;
        std::cout << arg << std::endl;
    } else if (functions.find(fun_name) != functions.end()){
        
        Function f = functions[fun_name];
        f.arg_value = arg; 
        std::vector<Token> body = f.body;

        reverse(body.begin(), body.end()) ;
        for (Token t : body){
            stack.push_back(t);
            stack_context.push_back(fun_name);
        }
        reverse(body.begin(), body.end()) ;

    } else {
        std::string msg = "Function " + fun_name + " not found (call_function)";
        throw InterpreterException(-2,-2,-2,-2, msg);
    }

}

void Interpreter::run() {

    v_cout << "Running interpreter\n" ;
    v_cout << "Nb tokens: " << stack.size() << "\n\n";

    bool defining = true ;

    while (true) {
        actual_token = stack.back();
        actual_function = stack_context.back();
        stack.pop_back();
        stack_context.pop_back();
        
        
        if        (actual_token.get_attribute("action") == "gvardef"){
            std::string var_name = actual_token.get_attribute("name");
            
            def_var(var_name);

        } else if (actual_token.get_attribute("action") == "gfundef"){
            std::string fun_name = actual_token.get_attribute("name");
            std::string argument = actual_token.get_attribute("arg");
            
            v_cout << "Defining function " << fun_name << std::endl;

            Function f = Function(fun_name, argument,actual_token.childs);
            functions.insert(std::make_pair(fun_name, f));

        } else if (actual_token.get_attribute("action") == "varset"){

            set_var(actual_token.get_attribute("name"), get_value(actual_token.childs[0]));
            
        } else if (actual_token.get_attribute("action") == "function"){
            
            std::string fun_name = actual_token.get_attribute("name");
            int arg = get_value(actual_token.childs[0]);
            call_function(fun_name, arg);
            
        } else if (actual_token.get_attribute("action") == "return"){

            last_value = get_value(actual_token.childs[0]);
            v_cout << "Return in " << actual_function << std::endl;
            
        } else {
            v_cout << "Unknown action: " << actual_token.get_attribute("action") << std::endl ;
            actual_token.print();
            throw InterpreterException(actual_token, "Unknown action");
        }

        if (stack.size() == 0 && defining){
            call_function("main", 0);
            defining = false;
        } else if (stack.size() == 0){
            break;
        }

    }

    return ;
}














