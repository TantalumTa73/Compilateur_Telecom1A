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
    vector<Token*> body = actual_token->children();
    reverse(body.begin(), body.end());
    for (auto t : body) { 
        // v_cout << "---> " << t->name << " <--- pushed in stack\n";
        stack.push_back(t);
    }
}

void Compiler::push_called_token(){
    int n = actual_token->children().size();
    actual_token->remained_children = n;
    called_tokens.push_back(actual_token);
    if (n == 0){
        pop_called_token();
        return;
    } else {
        reversed_children_push();
    }
}

void Compiler::pop_called_token(){
    if (called_tokens.size() <= 0){
        return;
    }
    called_tokens.back()->remained_children -= 1;

    if (called_tokens.back()->remained_children <= 0) {
        called_tokens.back()->on_exit();
        // v_cout << "---> " << actual_token->name << " <--- pop in  called_tokens\n";
        called_tokens.pop_back();
        pop_called_token();
    }
}

void Compiler::free_tokens(Token* token){
    if (token->children().size() > 0){}
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
        actual_token->on_enter();

        push_called_token();
    }
    //file.s
    end();
    free_tokens(root);
}