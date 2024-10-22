#pragma once
#include <unordered_map>
#include "define.hpp"



struct Variable {

    public:
        string name;
        string fun_name;
        int offset;
        bool is_arg;
        Variable();
        Variable(string name, string fun_name, int offset, bool is_arg);
};

class Context {

    public:

        const string name;
        unordered_map<string, Variable> vars;

        Context();
        Context(string name_);

        void init_var(string var_name, bool is_arg);

    private:
        int var_offset;
        int arg_offset;
};

extern std::unordered_map<std::string, Context> contexts ;
extern std::vector<std::string> called_contexts ;

Variable find_var(string name);

// Find var
// class context
// Pile of context
// dict context