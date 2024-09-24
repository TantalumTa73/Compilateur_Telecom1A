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
    root = Token();
    gvar = std::unordered_map<std::string, int>();
    functions = std::unordered_map<std::string, Function>();
    return;
}

Interpreter::Interpreter(Token root_) {
    root = root_;
    gvar = std::unordered_map<std::string, int>();
    functions = std::unordered_map<std::string, Function>();
    return;
}


int Interpreter::get_var(std::string var_name){

    if (functions.find(actual_function) == functions.end()){

        std::string msg = "Function " + actual_function + " not found";
        throw InterpreterException(actual_token, msg);

    } else if (functions[actual_function].get_var(var_name).has_value()){

        return functions[actual_function].get_var(var_name).value();

    } else if (gvar.find(var_name) != gvar.end()){

        return gvar[var_name] ;

    } else {
        std::string msg = "Variable " + var_name + " not found";
        throw InterpreterException(actual_token, msg);
    }
    
    return -1;

}

void Interpreter::set_var(std::string var_name, int value){

    if (functions.find(actual_function) == functions.end()){

        std::string msg = "Function " + actual_function + " not found";
        throw InterpreterException(actual_token, msg);

    } else if (functions[actual_function].get_var(var_name).has_value()){

        v_cout << "Set local variable " << var_name << " to " << value << std::endl;
        functions[actual_function].set_var(var_name, value);

    } else if (gvar.find(var_name) != gvar.end()){

        v_cout << "Set global variable " << var_name << " to " << value << std::endl;
        gvar[var_name] = value;

    } else {
        std::string msg = "Variable " + var_name + " not found";
        throw InterpreterException(actual_token, msg);
    }
    
    return ;
}

int Interpreter::get_value(Token token){


    if (token.get_attribute("type") == "cst"){
        v_cout << "\t Constant\n" ;
        return std::stoi(token.get_attribute("value"));

    } else if (token.get_attribute("type") == "var"){
        v_cout << "\t Variable\n" ;
        return get_var(token.get_attribute("name"));

    } else if (token.get_attribute("type") == "operation"){
        v_cout << "\t Operation\n" ;


    } else if (token.get_attribute("action") == "function"){
        v_cout << "\t Function\n" ;


    } else {
        v_cout << "\t Unknown :" << token.get_attribute("type") << std::endl;
    }

    return -1;
}

void Interpreter::call_function(){
    std::string fun_name = actual_token.get_attribute("name");
    std::string argument = actual_token.get_attribute("arg");
    v_cout << "Calling function " << fun_name << std::endl;

    if (fun_name == "print"){
        v_cout << "Printing " << get_var(argument) << std::endl;
    } else {
        std::string msg = "Function " + fun_name + " not found";
        throw InterpreterException(actual_token, msg);
    }

}

void Interpreter::run() {

    v_cout << "Printing tree" << std::endl;
    for (Token t : root.childs) t.print();
    v_cout << std::endl;

    v_cout << "Running interpreter" << std::endl;

    std::vector<Token> stack;
    stack.push_back(root);
    // Token token ;
    actual_function = "__root__";

    while (stack.size() > 0) {
        actual_token = stack.back();
        stack.pop_back();
        

        if (actual_token.get_attribute("name") == "__root__"){
            reverse(actual_token.childs.begin(), actual_token.childs.end()) ;
            for (Token t : actual_token.childs) stack.push_back(t);
            reverse(actual_token.childs.begin(), actual_token.childs.end()) ;

        } else if (actual_token.get_attribute("action") == "gvardef"){
            std::string var_name = actual_token.get_attribute("name");
            v_cout << "Defining global variable " << var_name << std::endl;
            gvar[var_name] = 0;

        } else if (actual_token.get_attribute("action") == "gfundef"){
            std::string fun_name = actual_token.get_attribute("name");
            std::string argument = actual_token.get_attribute("arg");
            
            v_cout << "Defining function " << fun_name << std::endl;

            Function f = Function(fun_name, argument);
            functions.insert(std::make_pair(fun_name, f));
            actual_function = fun_name;

            reverse(actual_token.childs.begin(), actual_token.childs.end()) ;
            for (Token t : actual_token.childs) stack.push_back(t);
            reverse(actual_token.childs.begin(), actual_token.childs.end()) ;

        } else if (actual_token.get_attribute("action") == "varset"){

            set_var(actual_token.get_attribute("name"), get_value(actual_token.childs[0]));
            
        } else if (actual_token.get_attribute("action") == "function"){
            
            call_function();
            
        } else if (actual_token.get_attribute("action") == "return"){
            v_cout << "Return in " << actual_function << std::endl;

            
        } else {
            v_cout << "Unknown action: " << actual_token.get_attribute("action") ;
            v_cout << " in line " << actual_token.start_line ;
            v_cout << " char " << actual_token.start_char ;
            v_cout << " to line " << actual_token.end_line ;
            v_cout << " char " << actual_token.end_char << std::endl;
        }


    }

    return ;
}














