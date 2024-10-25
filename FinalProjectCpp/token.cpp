#include <assert.h>
#include "token.hpp"

#include "subclasses/arg.hpp"
#include "subclasses/expr.hpp"
#include "subclasses/gstmt.hpp"
#include "subclasses/left_val.hpp"
#include "subclasses/litteral.hpp"
#include "subclasses/root.hpp"
#include "subclasses/stmt.hpp"

void Token::print(string indent){
    v_cout << indent << "Token: " << "\n";
}

// Token::Token(JSON* json) {
//     // A non recursive function that will create a Token from a JSON object
//     // type = "" ;

//     if (json == nullptr)
//         ERROR("Token : json is null");

//     // vector<Tk> tokens = vector<Tk>();
//     // vector<string> keys = vector<string>();

//     // Root* root = new Root();

//     // while (tokens.size() > 0){
//     //     Tk token = tokens.back();
//     //     tokens.pop_back();

//     //     if (token->type == "GStmt"){
//     //         root->gstmts.push_back((GStmt*) token);
//     //     }
//     // }
//     // if (json->has_string("type")) type = json->get_string("type");
//     // else ERROR("Error in Token : no type\n");
// }

Token* Token::simplify(JSON* json){

    if (json == nullptr){
        ERROR("Token : json is null");
    } else if (json->is_null()){
        return nullptr;
    } else if (!json->has_key("action")){
        ERROR("Error in Token : no action\n");
    } else if (! json->has_string("action")){
        ERROR("Error in Token : no string type\n");
    }

    string action = json->get_string("action");

    // v_cout << "simplify : " << action << "\n";

    if        (action == "__root__"){
        vector<GStmt*> gstmts = simplify<GStmt*>(json->get_array("gstmts"));
        return new Root(gstmts);


    } else if (action == "fundef"){ // gstmt
        string type = json->get_string("type");
        string name = json->get_string("name");
        vector<Arg*> args = simplify<Arg*>(json->get_array("args"));
        Stmt* body = (Stmt*) simplify(json->get_object("body"));
        return new GFunDef(type, name, args, body);
    } else if (action == "gvardef"){
        string type = json->get_string("type");
        string name = json->get_string("name");
        string array_size = json->get_string("size");
        // v_cout << "array_size : " << array_size << "\n";
        int array_size_int = stoi(array_size);
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new GVarDef(type, name, array_size_int, value);


    } else if (action == "arg"){ // arg
        string type = json->get_string("type");
        string name = json->get_string("name");
        return new Arg(type, name);


    } else if (action == "scope"){ // stmt
        vector<Stmt*> body = simplify<Stmt*>(json->get_array("body"));
        return new Sscope(body);
    } else if (action == "return"){
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new Sreturn(value);
    } else if (action == "for"){
        Stmt* init = (Stmt*) simplify(json->get_object("init"));
        Expr* cond = (Expr*) simplify(json->get_object("cond"));
        Stmt* update = (Stmt*) simplify(json->get_object("update"));
        Stmt* body = (Stmt*) simplify(json->get_object("body"));
        return new Sfor(init, cond, update, body);
    } else if (action == "while"){
        Expr* condition = (Expr*) simplify(json->get_object("condition"));
        Stmt* body = (Stmt*) simplify(json->get_object("body"));
        return new Swhile(condition, body);
    } else if (action == "vardef"){
        string type = json->get_string("type");
        DataType type_enum = data_type(type);
        string name = json->get_string("name");
        string array_size = json->get_string("size");
        int array_size_int = stoi(array_size);
        Expr* value = (Expr*) simplify(json->get_object("value"));
        return new SvarDef(type_enum, name, array_size_int, value);
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
        Stmt* body = (Stmt*) simplify(json->get_object("body"));
        return new Sif(condition, body);
    } else if (action == "ifelse") {
        Expr* condition = (Expr*) simplify(json->get_object("condition"));
        Stmt* body_if = (Stmt*) simplify(json->get_object("body_if"));
        Stmt* body_else = (Stmt*) simplify(json->get_object("body_else"));
        return new SifElse(condition, body_if, body_else);


    } else if (action == "void") { // litteral
        return new Void();
    } else if (action == "int") {
        string value = json->get_string("value");
        int val = stoi(value);
        return new Int(val);
    } else if (action == "char") {
        string value = json->get_string("value");
        char c = value[0];
        return new Char(c);
    } else if (action == "bool") {
        bool value = json->get_bool("value");
        return new Bool(value);


    } else if (action == "varget") { //left val
        string name = json->get_string("name");
        return new VarGet(name);
    } else if (action == "arrayget") {
        LeftValue* left_value = (LeftValue*) simplify(json->get_object("left_value"));
        Expr* index = (Expr*) simplify(json->get_object("index"));
        return new ArrayGet(left_value, index);
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
        // T new_t = (T) simplify(json);
        T new_t = dynamic_cast<T>(simplify(json));
        assert(new_t != nullptr);
        new_tokens.push_back( new_t );
    }

    return new_tokens;
}