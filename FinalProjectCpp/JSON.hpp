#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "define.hpp"

class JSON {

    public:
        JSON();
        JSON(string filename);

        string get_string(string key);
        int get_int(string key);
        bool get_bool(string key);
        vector<JSON*>* get_array(string key);
        JSON* get_object(string key);

        bool has_string(string key);
        bool has_int(string key);
        bool has_bool(string key);
        bool has_array(string key);
        bool has_object(string key);
        bool has_key(string key);

        bool is_null();

        void print(string indent = "");

    private:
        unordered_map<string, string> string_map;
        unordered_map<string, int> int_map;
        unordered_map<string, bool> bool_map;
        unordered_map<string, vector<JSON*>*> array_map;
        unordered_map<string, JSON*> object_map;
};