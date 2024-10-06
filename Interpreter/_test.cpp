#include <vector>
#include <string>

#include "simplified_token.hpp"



// void test(){

//     Token tk = Token(0,0,0,0);
//     SimplifiedToken base = SimplifiedToken(tk, VOID);
//     VarDef ret = VarDef(tk,"var def (ret)");
//     SimplifiedToken ret_tk = VarDef(tk,"var def (ret_tk)");
//     SimplifiedToken *ret_p = &ret;
//     SimplifiedToken ret_cp = ret;
//     SimplifiedToken &ret_ref = ret;
//     VarDef *ret_p2 = static_cast<VarDef*>(&ret_tk);
//     VarDef ret2 = *ret_p2;
//     std::unique_ptr<SimplifiedToken> ret_p3 = std::make_unique<VarDef>(ret);
//     std::unique_ptr<SimplifiedToken> ret_p4 = std::make_unique<SimplifiedToken>(ret);

//     v_cout << "base\t" ; base.print();
//     v_cout << "ret_tk\t" ; ret_tk.print();
//     v_cout << "ret_cp\t" ; ret_cp.print();
//     v_cout << "ret_p2\t" ; ret_p2->print();
//     v_cout << "ret2 \t" ; ret2.print();         // error 
//     v_cout << "ret_p4\t" ; ret_p4->print();

//     v_cout << "ret\t" ; ret.print();            // valid
//     v_cout << "ret_p\t" ; ret_p->print();       // valid
//     v_cout << "ret_ref\t" ; ret_ref.print();    // valid
//     v_cout << "ret_p3\t" ; ret_p3->print();     // valid


//     v_cout << "\n" ;
// }

void test_vect(){
    std::cout << "test_vect\n";
    Token tk = Token(0,0,0,0);
    VarDef ret = VarDef(tk,"var_name");
    // SimplifiedToken base = SimplifiedToken(tk, VOID);
    SimplifiedToken *ret_tk = (SimplifiedToken*) &ret;
    // SimplifiedToken ret2 = *ret_tk;


    
    // std::vector<TkPtr> vect;
    // vect.push_back(std::make_unique<VarDef>(ret));
    std::vector<SimplifiedToken*> vect;
    // vect.push_back(&ret);
    // vect.push_back(&base);

    vect.back()->print();
    // SimplifiedToken* ret_ref = vect.back();
    // SimplifiedToken* ret_ref = dynamic_cast<SimplifiedToken*>(vect.back());
    // SimplifiedToken* ret_ref = dynamic_cast<VarDef*>(vect.back());
    // VarDef *ret_ref = dynamic_cast<VarDef*>(vect.back());
    VarDef *ret_ref = dynamic_cast<VarDef*>(ret_tk);
    std::cout << "ptr : " << ret_ref << " " << (ret_ref == nullptr )<< std::endl;
    // ret_ref.print();
    // ret_ref.var_name = "new_name";
    // ret_ref.print();
    ret_ref->print();
    // ret_ref->var_name = "new_name";
    // ret_ref->print();
}


////////////////////////////////////////

void add_v(std::vector<SimplifiedToken*> &v){
    Token tk = Token(0,0,0,0);
    // SimplifiedToken base = SimplifiedToken(tk, VOID);
    VarDef ret = VarDef(tk,"var def (ret)");
    
    // SimplifiedToken ret_tk = VarDef(tk,"var def (ret_tk)");
    SimplifiedToken *ret_p = &ret;
    // SimplifiedToken ret_cp = ret;
    SimplifiedToken &ret_ref = ret;
    // VarDef *ret_p2 = static_cast<VarDef*>(&ret_tk);
    // VarDef ret2 = *ret_p2;
    std::unique_ptr<SimplifiedToken> ret_p3 = std::make_unique<VarDef>(ret);
    // std::unique_ptr<SimplifiedToken> ret_p4 = std::make_unique<SimplifiedToken>(ret);

    // v.push_back(new SimplifiedToken(tk, VOID));
    v.push_back(new VarDef(tk,"var def (ret)"));
    // v.push_back(&ret);
    // v.push_back(&ret_tk);
    // v.push_back(&ret_cp);
    // v.push_back(&ret_ref);
    // v.push_back(&ret2);
}

void vect_ptr_test(){
    std::vector<SimplifiedToken*> v;
    add_v(v);
    std::cout << v.size() << std::endl;
    for (auto e : v){
        std::cout << "e: " ;
        e->print();
    }

    
}


////////////////////////////////////////

void add_v(std::vector<std::unique_ptr<SimplifiedToken>> &v){

    Token tk = Token(0,0,0,0);
    // SimplifiedToken base = SimplifiedToken(tk, VOID);
    VarDef vard = VarDef(tk,"var def (ret)");
    Return ret = Return(tk);
    Operator op = Operator(tk,"plus",2);

    v.push_back(std::make_unique<VarDef>(vard));
    v.push_back(std::make_unique<Return>(ret));
    v.push_back(std::make_unique<Operator>(op));

}

void match_f(std::unique_ptr<SimplifiedToken> &e){
    std::cout << "SimplifiedToken\n";
}
void match_f(std::unique_ptr<VarDef> &e){
    std::cout << "VarDef\n";
}
void match_f(std::unique_ptr<Return> &e){
    std::cout << "Return\n";
}

void match_tk(Operator* e){ std::cout << "Operator\n";}
void match_tk(Return* e){ std::cout << "Return\n";}
void match_tk(VarDef* e){ std::cout << "VarDef\n";}
// void match_tk(SimplifiedToken* e){ std::cout << "SimplifiedToken\n";}

void match_tk2(SimplifiedToken* e){
    if (dynamic_cast<Operator*>(e) != nullptr){
        std::cout << "Operator\n";
    } else if (dynamic_cast<Return*>(e) != nullptr){
        std::cout << "Return\n";
    } else if (dynamic_cast<VarDef*>(e) != nullptr){
        std::cout << "VarDef\n";
    } else {
        std::cout << "SimplifiedToken\n";
    }
}

void vect_smart_ptr_test(){
    std::vector<std::unique_ptr<SimplifiedToken>> v;
    add_v(v);
    std::cout << v.size() << std::endl;
    for (auto& e : v){
        std::cout << "e: " ;
        e->print();
        match_f(e);
    }

    std::cout << "\n";
    
    // VarDef original_tk = VarDef(Token(0,0,0,0),"var def (ret)");
    Operator original_tk = Operator(Token(0,0,0,0),"plus",2);
    std::unique_ptr<SimplifiedToken> uptr = std::make_unique<Operator>(original_tk);
    SimplifiedToken* ptr = &original_tk;
    
    // TkPtr& tk = uptr;
    SimplifiedToken* tk = ptr;
    std::unique_ptr<SimplifiedToken> tk2 = std::move(uptr);
    Operator* op = static_cast<Operator*>(ptr);
    Return* ret = static_cast<Return*>(ptr);
    VarDef* vard = static_cast<VarDef*>(ptr);
    std::cout << "tk  : " << tk << std::endl;
    std::cout << "op  : " << op << std::endl;
    std::cout << "ret : " << ret << std::endl;
    std::cout << "vard: " << vard << std::endl;
    tk->print();
    op->print();
    ret->print();
    vard->print();
    match_tk2(tk);
    match_tk2(op);
    match_tk2(ret);
    match_tk2(vard);
    
}

////////////////////////////////////////

void test_ptr(){

    Operator* op = new Operator(Token(0,0,0,0),"plus",2);
    SimplifiedToken* tk = new Operator(Token(0,0,0,0),"plus",2);

    op->print();
    tk->print();

}


void testing(){

    // test();
    // vect_ptr_test();
    vect_smart_ptr_test();
    test_ptr();

    return ;
}

// https://stackoverflow.com/questions/37237358/c-make-pointer-to-superclass-match-subclass-argument-in-function
// https://stackoverflow.com/questions/10338548/making-a-vector-of-instances-of-different-subclasses
// https://en.cppreference.com/w/cpp/language/dynamic_cast