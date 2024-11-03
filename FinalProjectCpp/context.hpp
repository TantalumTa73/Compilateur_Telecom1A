#pragma once
#include <unordered_map>
#include "define.hpp"
#include <vector>


struct Variable {

    public:
        string name;
        string ctx_name;
        int adress;
        bool is_arg;
        Variable();
        Variable(string name, string fun_name, int offset, bool is_arg);
        string get_adress(int shift = 0);
};

class Context {

    public:

        const string name;
        unordered_map<string, Variable> vars;

        Context();
        Context(string name_, int offset = 0);

        void init_var(string var_name, int size, bool is_arg);

        int var_offset;
    private:
        int arg_offset;
};

extern std::unordered_map<string, Context> contexts ;
extern std::vector<string> called_contexts ;

Variable find_var(string name);

// Find var
// class context
// Pile of context
// dict context