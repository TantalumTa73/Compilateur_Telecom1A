#include <assert.h>
#include "compiler.hpp"
#include "write_assembly.hpp"


void Compiler::init_compiling(){
    
    stack = vector<Token*>();
    called_tokens = vector<Token*>();

    Context empty_f = Context();
    contexts.insert({PRINT, empty_f});
    contexts.insert({READ, empty_f});
    Context global_f = Context(GLOBAL);
    contexts.insert({GLOBAL, global_f});
    called_contexts.push_back(GLOBAL);

    init();
}

void Compiler::reversed_children_push(){
    // Push children in reverse order
    vector<Token*> body = actual_token->children();
    reverse(body.begin(), body.end());
    for (auto t : body) {
        stack.push_back(t);
        v_cout << "|||> Pushed " << t->tk_type << " in stack\n";
    }
}

// Make calulation for the actual node
// void Compiler::run_node(){
// }

// Call on_exit() of if all children are done
void Compiler::exit_token(){
    // If all children are done, call on_exit() and pop the node
    
    // while (true){
    while (called_tokens.size() > 0 && --called_tokens.back()->remained_children <= 0){
        
        called_tokens.back()->on_exit();
        // v_cout << "|||< Popped " << called_tokens.back()->tk_type << " in stack\n";
        called_tokens.pop_back();
    }
    
}

void Compiler::free_tokens(Token* token){
    // if (token->children_().size() > 0){}
    //     for (auto child: token->children){
    //         free_tokens(child);
    //     }
    // }
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


        actual_token->on_enter();
        actual_token->remained_children = actual_token->children().size();


        if (actual_token->remained_children > 0) reversed_children_push();
        else exit_token();

    }
    //file.s
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