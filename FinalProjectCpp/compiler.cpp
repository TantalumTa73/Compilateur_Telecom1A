#include <assert.h>
#include "compiler.hpp"
#include "write_assembly.hpp"


void Compiler::init_compiling(){
    
    stack = vector<Token*>();
    called_tokens = vector<Token*>();
    break_stack = vector<string>();
    continue_stack = vector<string>();

    Context empty_f = Context();
    contexts.insert({PRINT_INT, empty_f});
    contexts.insert({PRINT_CHAR, empty_f});
    contexts.insert({PRINTF, empty_f});
    contexts.insert({PRINTF, empty_f});

    contexts.insert({SCAN_INT, empty_f});

    contexts.insert({MALLOC, empty_f});

    Context global_f = Context(GLOBAL);
    contexts.insert({GLOBAL, global_f});
    called_contexts.push_back(GLOBAL);

    init();
}

void Compiler::reversed_children_push(){
    // Push children in reverse order

    // string label_start = (continue_stack.size() > 0) ? continue_stack.back() : "";
    // string label_end = (break_stack.size() > 0) ? break_stack.back() : "";
    // string arg = "";
    // if (actual_token != nullptr && actual_token->tk_type == KEYWORD){
    //     Skeyword* keyword = dynamic_cast<Skeyword*>(actual_token);
    //     assert(keyword != nullptr);
    //     if(keyword->keyword == "break"){
    //         arg = label_end;
    //     } else if (keyword->keyword == "continue"){
    //         arg = label_start;
    //     }
    // }
    vector<Token*> body = actual_token->children();
    actual_token->remained_children = body.size();
    reverse(body.begin(), body.end());

    for (auto t : body) stack.push_back(t);
}


void Compiler::exit_token(){
    // If all children are done, call on_exit() and pop the node
    
    while (called_tokens.size() > 0 && called_tokens.back()->remained_children-- <= 0){
        
        called_tokens.back()->on_exit();
        if (called_tokens.back()->tk_type == FOR || 
            called_tokens.back()->tk_type == WHILE){
            break_stack.pop_back();
            continue_stack.pop_back();
        }
        called_tokens.pop_back();
    }
    
}

void Compiler::free_tokens(Token* token){
    if (token == nullptr) return;
    // delete token;
}

void Compiler::run(){
    init_compiling();

    stack.push_back(root);
    while (stack.size() > 0){
        
        actual_token = stack.back();
        assert(actual_token != nullptr);
        stack.pop_back();
        called_tokens.push_back(actual_token);

        if (actual_token->tk_type == FOR){
            Sfor* for_token = (Sfor*)actual_token;
            assert(for_token != nullptr);
            continue_stack.push_back(for_token->label_update->label);
            break_stack.push_back(for_token->label_end->label);
        }
        if (actual_token->tk_type == WHILE){
            Swhile* while_token = (Swhile*)actual_token;
            assert(while_token != nullptr);
            continue_stack.push_back(while_token->label_start->label);
            break_stack.push_back(while_token->label_end->label);
        }

        actual_token->on_enter();

        reversed_children_push();
        exit_token();

    }
    //file.s

    if (contexts.find(MAIN) == contexts.end()){
        v_cout << "No main function" << endl;
        w_init_f(MAIN);
        w_ret(true);
    }

    end();
    free_tokens(root);
}

/*
For each node :
- Call on_enter() of the node
- Push it on called_tokens
- Push children in reverse order on the stack

- Treat the children in the stack

- call on_exit() of the node
- pop the node from the stack


called_tokens is a stack of nodes that have been called and not yet exited

*/