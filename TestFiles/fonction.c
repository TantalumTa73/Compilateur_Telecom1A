

int u ;
u = 18 ; 

int g ( int b ) {
    return b + 1;
}

int f ( int b ) {
    return 2 * g(b);
}

int h ( int v ) {
    int b ;
    b = 12 ;
    print(b) ;
    v = 5 ;
    print(v) ;
    return v ;
}

int main ( int a ) {
    a=0 ;
    print(a) ;
    print(u) ;

    int b ;
    b = 42 ;

    h(a);

    print(b);

    u = f(2);

}