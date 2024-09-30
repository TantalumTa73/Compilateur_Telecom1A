int x ;

int def_local (int a){
    print(a);
    int x ;
    x = a ;
    print(x);
    return 0 ;
}

int modify_global (int a){
    x = x + a ;
    return 0 ;
}

int get_global (int a){
    print(x);
    return 0 ;
}

int main (int a){
    
    x = 1 ;
    print(x);

    def_local(2);
    print(x);

    modify_global(3);
    print(x);

    return 0 ;
}