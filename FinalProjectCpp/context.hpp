#pragma once
#include <unordered_map>
#include <vector>
#include "token.hpp"


struct Variable {

    public:
        string name;
        string ctx_name;
        int address;
        bool is_arg;
        int type_size ;
        int full_size ;
        vector<int> ladder_size;
        Variable();
        Variable(string name, string fun_name, int offset, bool is_arg,
            int type_size, vector<int> ladder_size);
        string get_adress(int shift = 0);
};

class Context {

    public:

        const string name;
        unordered_map<string, Variable> vars;

        Context();
        Context(string name_, int offset = 0);

        int init_var(string var_name, int type_size, vector<int> ladder_size, bool is_arg);

        int var_offset;
    private:
        int arg_offset;
};

extern std::unordered_map<string, Context> contexts ;
extern std::vector<string> called_contexts ;

Variable find_var(string name);
