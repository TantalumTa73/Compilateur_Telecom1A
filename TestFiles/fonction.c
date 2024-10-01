

int u ;
int v;

v = 3 ;
u = 5 ; 


int g ( int b ) {
    int c;
    read(c);
    print(c);
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
    read(v);
    print(73*v);
    return v;
}

int main ( int a ) {
    a=0 ;
    print(a) ;
    print(u * 3) ;

    int b ;
    b = 42 ;

    h(a);

    print(b);
    read(b);
    print(3*b);

    u = f(2);

    print(v);
    read(v);
    print(7*v);

}