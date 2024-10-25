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
        string get_adress();
};

class Context {

    public:

        const string name;
        unordered_map<string, Variable> vars;

        Context();
        Context(string name_);

        void init_var(string var_name, int size, bool is_arg);

    private:
        int var_offset;
        int arg_offset;
};

extern std::unordered_map<string, Context> contexts ;
extern vector<string> called_contexts ;

Variable find_var(string name);

// Find var
// class context
// Pile of context
// dict context