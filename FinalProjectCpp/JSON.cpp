#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "JSON.hpp"

string JSON::get_string(string key){
    return string_map[key];
}
int JSON::get_int(string key){
    return int_map[key];
}
bool JSON::get_bool(string key){
    return bool_map[key];
}
vector<JSON*>* JSON::get_array(string key){
    return array_map[key];
}
JSON* JSON::get_object(string key){
    return object_map[key];
}

JSON::JSON(){

    string_map = unordered_map<string, string>();
    int_map = unordered_map<string, int>();
    bool_map = unordered_map<string, bool>();
    array_map = unordered_map<string, vector<JSON*>*>();
    object_map = unordered_map<string, JSON*>();

    return ;
}

struct tree_node {
    JSON* json ;
    vector<JSON*>* vect ;

    tree_node(JSON* json){
        this->json = json;
        this->vect = nullptr;
    }
    tree_node(vector<JSON*>* vect){
        this->json = nullptr;
        this->vect = vect;
    }
};

JSON::JSON(string filename){

    JSON();

    std::ifstream file = std::ifstream(filename);

    if (!file.is_open()) {
        string msg = "Error opening file: " + filename + "\n";
        ERROR(msg);
    }

    vector<tree_node> tree = vector<tree_node>();
    // vector<string> keys = vector<string>();

    tree.push_back(tree_node(this));
    this->string_map["type"] = "__root__";
    
    std::string name = "data";
    std::string value ;
    bool is_name;
    char c ;

    while ( ! file.eof() ) {
        c = file.get();
        
        if (c == '{' ){
            if (tree.back().vect != nullptr){
                JSON* json = new JSON();
                tree.back().vect->push_back(json);
                tree.push_back(tree_node(json));

            } else if (tree.back().json != nullptr){
                JSON* json = new JSON();
                tree.back().json->object_map[name] = json ;
                tree.push_back(tree_node(json));
            } else ERROR("Error in JSON : bizzard tree_node\n");

            name = "" ;
            value = "" ;
            is_name = true ;

        } else if (c == '['){
            if (tree.back().vect != nullptr){
                ERROR("Error in JSON : array of array\n");
            } else if (tree.back().json != nullptr) {
                vector<JSON*>* vect = new vector<JSON*>();
                tree.back().json->array_map[name] = vect;
                tree.push_back(tree_node(vect));
            }
        
            name = "" ;
            value = "" ;
            is_name = true ;

        } else if (c == ',' || c == '}' || c == ']'){
            
            if (value != ""){
                if (tree.back().vect != nullptr){
                    // tree.back().vect ;
                    std::cout << "Error in JSON : \',\' in vect\n";
                } else if (tree.back().json != nullptr){
                    tree.back().json->string_map[name] = value;
                }
            }

            name = "";
            value = "";
            is_name = true;
            
            if (c == '}' || c == ']'){
                if (tree.size() > 0) tree.pop_back();
                else ERROR("Error in JSON : tree.pop_back()\n");
            }
        }
        else if (c == ':' && is_name) {
            is_name = false;
        }
        else if (c == ':' && ! is_name) {
            std::cerr << "Error in file: " << filename << "\n";
            
            break;
        }
        else if (c != '\n' && c != '\t' && c != '\"' && c != ' '){
            if (is_name) name += c;
            else value += c;
        }        
    }

    file.close();

    return ;

}

void JSON::print(string indent){
    const string new_indent = "  ";
    for (auto it = string_map.begin(); it != string_map.end(); it++){
        v_cout << indent << '\'' << it->first << "\' : \'" << it->second << "\'\n";
    }
    for (auto it = int_map.begin(); it != int_map.end(); it++){
        v_cout << indent << it->first << " : " << it->second << "\n";
    }
    for (auto it = bool_map.begin(); it != bool_map.end(); it++){
        v_cout << indent << it->first << " : " << it->second << "\n";
    }
    for (auto it = array_map.begin(); it != array_map.end(); it++){
        v_cout << indent << "\'" << it->first << "\' : [\n";
        int i = 0;
        for (auto it2 = it->second->begin(); it2 != it->second->end(); it2++){
            v_cout << indent << new_indent << "[" << i++ << "] : {\n";
            (*it2)->print(indent + new_indent + new_indent);
        }
        v_cout << indent << "]\n";
    }
    for (auto it = object_map.begin(); it != object_map.end(); it++){
        v_cout << indent << "\'" << it->first << "\' : {\n";
        it->second->print(indent + new_indent);
        v_cout << indent << "}\n";
    }
    return ;
}
        