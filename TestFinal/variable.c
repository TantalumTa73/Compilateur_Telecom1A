int main(){

    int a = 0 ;

    print_int(a) ;      // 0

    a = 1 ;
    print_int(a) ;      // 1

    a += 2 ;
    print_int(a) ;      // 3
    a -= 1 ;
    print_int(a) ;      // 2

    a *= 2 ;
    print_int(a) ;      // 4
    a = 9 ;
    a /= 2 ;
    print_int(a) ;      // 4
    a = 9 ;
    a %= 2 ;
    print_int(a) ;      // 1

    // a = 11 ;
    // a <<= 1 ;
    // print_int(a) ;      // 22
    // a >>= 1 ;
    // print_int(a) ;      // 11


    // LRop
    int b = 10;
    print_int(b) ;
    print_int(b++) ;
    print_int(b) ;
    print_int(b--) ;
    print_int(b) ;
    print_int(&b) ;

    // LLop
    int c = 10 ;
    print_int(c) ;      // 10
    print_int(++c) ;    // 11
    print_int(c) ;      // 11
    print_int(--c) ;    // 11
    print_int(c) ;      // 11

    // RLop
    int d = 10 ;
    int* ptr ;
    ptr = &d ;
    print_int(d) ;
    print_int(ptr) ;
    print_int(*ptr) ;
    print_int(*&d) ;

    // Array
    int t[2] ;
    t[0] = 10 ;
    t[1] = 21 ;
    int i = 1;

    print_int(t[0]) ;
    print_int(t[1]) ;
    print_int(t[i]) ;

    return 0 ;
}