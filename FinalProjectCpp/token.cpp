#include <assert.h>
#include "token.hpp"

#include "subclasses/arg.hpp"
#include "subclasses/expr.hpp"
#include "subclasses/gstmt.hpp"
#include "subclasses/left_val.hpp"
#include "subclasses/litteral.hpp"
#include "subclasses/root.hpp"
#include "subclasses/stmt.hpp"

int _label_id = 1 ;
int _label_if_id = 1 ;
int _scope_id = 1 ;
vector<string> _string_stack = vector<string>();
// It is to update mult for ArrayGet
int _mult_tmp = 1;
bool _is_treating_array = false;
string _array_name;
vector<string> _scope_stack = vector<string>();

void Token::print(string indent){
    v_cout << indent << "Token: " << "\n";
}

/*
Token::Token(JSON* json) {
    // A non recursive function that will create a Token from a JSON object
    // type = "" ;

    if (json == nullptr)
        ERROR("Token : json is null");

    // vector<Tk> tokens = vector<Tk>();
    // vector<string> keys = vector<string>();

    // Root* root = new Root();

    // while (tokens.size() > 0){
    //     Tk token = tokens.back();
    //     tokens.pop_back();

    //     if (token->type == "GStmt"){
    //         root->gstmts.push_back((GStmt*) token);
    //     }
    // }
    // if (json->has_string("type")) type = json->get_string("type");
    // else ERROR("Error in Token : no type\n");
}
*/

Token* Token::simplify(JSON* json){

    if (json == nullptr){
        ERROR("Token : json is null");
        return nullptr;
    } else if (json->is_null()){
        return nullptr;
    } else if (!json->has_key("action")){
        ERROR("Error in Token : no action\n");
    } else if (!json->has_string("action")){
        ERROR("Error in Token : no string action\n");
    }

    string action = json->get_string("action");

    // v_cout << "simplify : " << action << "\n";

    if        (action == "__root__"){
        _scope_stack.push_back("__root__");
        vector<GStmt*> gstmts = simplify<GStmt*>(json->get_array("gstmts"));
        return new Root(gstmts);


    } else if (action == "fundef"){ // gstmt
        string type = json->get_string("type");
        string name = json->get_string("name");
        _scope_stack.push_back(name);
        vector<Arg*> args = simplify<Arg*>(json->get_array("args"));
        Stmt* body = (Stmt*) simplify(json->get_object("body"));
        // if (body->tk_type == SCOPE){
        //     Sscope* scope = (Sscope*) body;
        //     scope->name = name;
        // }
        _scope_stack.pop_back();
        return new GFunDef(type, name, args, body);
    } else if (action == "gvardef"){
        DataType type_enum = data_type(json->get_string("type"));
        string name = json->get_string("name");
        vector<int> size = simplify_int(json->get_array("size"));
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new GVarDef(type_enum, name, size, value);


    } else if (action == "arg"){ // arg
        string type = json->get_string("type");
        string name = json->get_string("name");
        return new Arg(type, name);


    } else if (action == "scope"){ // stmt
        int id = _scope_id++;
        string name = "scope_" + to_string(id);
        string ctx = _scope_stack.back();
        _scope_stack.push_back(name);
        vector<Stmt*> body = simplify<Stmt*>(json->get_array("body"));
        _scope_stack.pop_back();
        return new Sscope(name,body,ctx);
    } else if (action == "return"){
        Expr* value = (Expr*) simplify(json->get_object("value"));
        if (value != nullptr && value->tk_type == LITTERAL_VOID){
            value = nullptr;
        }
        return new Sreturn(value);
    } else if (action == "keyword"){
        string keyword = json->get_string("keyword");
        return new Skeyword(keyword, _label_id);
    } else if (action == "for"){
        int id = _scope_id++;
        string name = "scope_" + to_string(id);
        string ctx = _scope_stack.back();
        _scope_stack.push_back(name);
        Stmt* init = (Stmt*) simplify(json->get_object("init"));
        Expr* cond = (Expr*) simplify(json->get_object("condition"));
        Stmt* update = (Stmt*) simplify(json->get_object("update"));
        Stmt* body = (Stmt*) simplify(json->get_object("body"));
        int label = _label_id++;
        _scope_stack.pop_back();
        return new Sfor(name, init, cond, update, body, label, ctx);
    } else if (action == "while"){
        int id = _scope_id++;
        string name = "scope_" + to_string(id);
        string ctx = _scope_stack.back();
        _scope_stack.push_back(name);
        Expr* condition = (Expr*) simplify(json->get_object("condition"));
        Stmt* body = (Stmt*) simplify(json->get_object("body"));
        int label = _label_id++;
        _scope_stack.pop_back();
        return new Swhile(name, condition, body, label, ctx);
    } else if (action == "vardef"){
        DataType type_enum = data_type(json->get_string("type"));
        string name = json->get_string("name");
        vector<int> ladder_size = simplify_int(json->get_array("size"));
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new SvarDef(type_enum, name, value, ladder_size);

    } else if (action == "varset"){
        LeftValue* left_value = (LeftValue*) simplify(json->get_object("left_value"));
        string op = json->get_string("op");
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new SvarSet(left_value, op, value);
    } else if (action == "expr"){
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new Sexpr(value);
    } else if (action == "if") {
        Expr* condition = (Expr*) simplify(json->get_object("condition"));
        Stmt* body_if = (Stmt*) simplify(json->get_object("body"));
        int label = _label_if_id++;
        return new Sif(condition, body_if, label);
    } else if (action == "ifelse") {
        Expr* condition = (Expr*) simplify(json->get_object("condition"));
        Stmt* body_if = (Stmt*) simplify(json->get_object("body_if"));
        Stmt* body_else = (Stmt*) simplify(json->get_object("body_else"));
        int label = _label_if_id++;
        return new SifElse(condition, body_if, body_else, label);


    } else if (action == "void") { // litteral
        return new Void();
    } else if (action == "int") {
        string value = json->get_string("value");
        int val = stoi(value);
        return new Int(val);
    } else if (action == "bool") {
        string value = json->get_string("value");
        bool value_bool = (value == "1");
        return new Bool(value_bool);
    } else if (action == "char") {
        string value = json->get_string("value");
        char c = value[0];
        return new Char(c);
    } else if (action == "string") {
        string value = json->get_string("value");
        int length = value.size() + 1; // +1 for '\0'
        int id = _string_stack.size();
        _string_stack.push_back(value);
        return new String(value, id, length);

    } else if (action == "sizeof") {
        string value = json->get_string("value");
        return new SizeOf(value);

    } else if (action == "varget") { //left val
        string name = json->get_string("name");
        if (_is_treating_array){
            _is_treating_array = false;
            _mult_tmp = 1;
            _array_name = name;
        }
        return new VarGet(name);
    } else if (action == "arrayget") {
        int mult = _mult_tmp ++;
        _is_treating_array = true;
        LeftValue* left_value = (LeftValue*) simplify(json->get_object("left_value"));
        Expr* index = (Expr*) simplify(json->get_object("index"));
        return new ArrayGet(left_value, index, mult, _array_name);
    } else if (action == "llop") {
        LeftValue* left_value = (LeftValue*) simplify(json->get_object("left_value"));
        string op = json->get_string("op");
        return new LLop(left_value, op);
    } else if (action == "rlop") {
        Expr* value = (Expr*) simplify(json->get_object("value"));
        string op = json->get_string("op");
        return new RLop(op, value);


    } else if (action == "litteral") { // expr
        return (Litteral*) simplify(json->get_object("value"));
    } else if (action == "valueget") {
        LeftValue* value = (LeftValue*) simplify(json->get_object("value"));
        return new ValueGet(value);
    } else if (action == "list") {
        vector<Expr*> values = simplify<Expr*>(json->get_array("values"));
        return new List(values);
    } else if (action == "funcall") {
        string name = json->get_string("name");
        vector<Expr*> args = simplify<Expr*>(json->get_array("args"));
        return new FunCall(name, args);

    } else if (action == "lrop") {
        LeftValue* left_value = (LeftValue*) simplify(json->get_object("left_value"));
        string op = json->get_string("op");
        return new LRop(op,left_value);
    } else if (action == "uniop") {
        string uniop = json->get_string("uniop");
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new Uniop(uniop, value);
    } else if (action == "binop") {
        string binop = json->get_string("binop");
        Expr* v1 = (Expr*) simplify(json->get_object("v1"));
        Expr* v2 = (Expr*) simplify(json->get_object("v2"));
        if (binop == "&&") return new LazyAnd(v1, v2, _label_id++);
        if (binop == "||") return new LazyOr(v1, v2, _label_id++);
        return new Binop(binop, v1, v2);
    } else if (action == "ternop") {
        Expr* condition = (Expr*) simplify(json->get_object("condition"));
        Expr* v1 = (Expr*) simplify(json->get_object("v1"));
        Expr* v2 = (Expr*) simplify(json->get_object("v2"));
        return new Ternop(condition, v1, v2);
    }

    ERROR("Error in Token : no action named \'" + action + "\'\n");
    return nullptr;
}

template<typename T>
vector<T> Token::simplify(vector<JSON*>* vect){

    if (vect == nullptr)
        ERROR("Token : vect is null");

    vector<T> new_tokens = vector<T>();
    reverse(vect->begin(), vect->end()) ;
   
    while (vect->size() > 0){
        JSON* json = vect->back();
        vect->pop_back();
        T new_t = dynamic_cast<T>(simplify(json));
        assert(new_t != nullptr);
        new_tokens.push_back( new_t );
    }

    return new_tokens;
}

vector<int> Token::simplify_int(vector<JSON*>* vect){

    if (vect == nullptr)
        ERROR("Token : vect is null");

    vector<int> new_tokens = vector<int>();
    reverse(vect->begin(), vect->end()) ;
   
    while (vect->size() > 0){
        JSON* json = vect->back();
        vect->pop_back();
        int val = json->get_int("value");
        new_tokens.push_back( val );
    }

    return new_tokens;
}
