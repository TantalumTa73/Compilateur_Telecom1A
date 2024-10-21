#include "compiler.hpp"
#include "write_assembly.hpp"

Compiler::Compiler(std::string cfilename_) {
    cfilename = cfilename_;
    return;
}

/*
void Compiler::init_registers(){
    registers_name.insert({"rax", std::nullopt});
    registers_name.insert({"rbx", std::nullopt});
    registers_name.insert({"rcx", std::nullopt});
    registers_name.insert({"rdx", std::nullopt});
    registers_name.insert({"rsi", std::nullopt});
    registers_name.insert({"rdi", std::nullopt});
    registers_name.insert({"rsp", std::nullopt});
    registers_name.insert({"rbp", std::nullopt});
    registers_name.insert({"r8", std::nullopt});
    registers_name.insert({"r9", std::nullopt});
    registers_name.insert({"r10", std::nullopt});
    registers_name.insert({"r11", std::nullopt});
    registers_name.insert({"r12", std::nullopt});
    registers_name.insert({"r13", std::nullopt});
    registers_name.insert({"r14", std::nullopt});
    registers_name.insert({"r15", std::nullopt});
}
*/

void Compiler::init_compiling(){
    //registers_name = std::unordered_map<std::string, std::optional<int>>();
    stack = std::vector<Token*>();
    called_tokens = std::vector<Token*>();
    //active_registers = std::vector<int>();
    //init_registers();

    Function empty_f = Function();
    functions.insert({PRINT, empty_f});
    functions.insert({READ, empty_f});
    Function global_f = Function(GLOBAL);
    functions.insert({GLOBAL, global_f});
    called_fun_names.push_back(GLOBAL);

    std::string jsonfilename = cfilename.substr(0, cfilename.size() - 1) + "json";
    JsonReader reader(jsonfilename);
    root = reader.readFile();

    std::string sfilename = cfilename.substr(0, cfilename.size() - 1) + "s";
    init(sfilename);
}

void Compiler::reversed_children_push(){
    std::cout << "entering in reversed_children_push (compiler.cpp)\n";
    std::vector<Token*> body = actual_token->children;
    reverse(body.begin(), body.end());
    for (auto t : body) { 
        std::cout << "---> " << t->name << " <--- pushed in stack\n";
        stack.push_back(t);
    }
}

void Compiler::push_called_token(){
    std::cout << "---> " << actual_token->name << " <--- pushed in called_tokens\n";
    int n = actual_token->children.size();
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
    std::cout << "entering in pop_called_token (compiler.cpp)\n";
    if (called_tokens.size() <= 0){
        return;
    }
    called_tokens.back()->remained_children -= 1;

    if (called_tokens.back()->remained_children <= 0) {
        called_tokens.back()->after_all_children_processed();
        std::cout << "---> " << actual_token->name << " <--- pop in  called_tokens\n";
        called_tokens.pop_back();
        pop_called_token();
    }
}

void Compiler::free_tokens(Token* token){
    if (token->children.size() > 0){
        for (auto child: token->children){
            free_tokens(child);
        }
    }
    delete token;
}

void Compiler::run(){
    init_compiling();

    stack.push_back(root);
    while (stack.size() > 0){
        actual_token = stack.back();
        std::cout << "---> " << actual_token->name << " <--- pop in stack\n";
        stack.pop_back();
        actual_token->on_enter();

        push_called_token();
    }
    //file.s
    end();
    free_tokens(root);
}