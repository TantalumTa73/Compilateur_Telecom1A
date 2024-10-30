int main(){

    int a = 0 ;

    print(a) ;      // 0

    a = 1 ;
    print(a) ;      // 1

    a += 2 ;
    print(a) ;      // 3
    a -= 1 ;
    print(a) ;      // 2

    a *= 2 ;
    print(a) ;      // 4
    a = 9 ;
    a /= 2 ;
    print(a) ;      // 4
    a = 9 ;
    a %= 2 ;
    print(a) ;      // 1

    // a = 11 ;
    // a <<= 1 ;
    // print(a) ;      // 22
    // a >>= 1 ;
    // print(a) ;      // 11


    // LRop
    int b = 10;
    print(b) ;
    print(b++) ;
    print(b) ;
    print(b--) ;
    print(b) ;
    print(&b) ;

    // LLop
    int c = 10 ;
    print(c) ;      // 10
    print(++c) ;    // 11
    print(c) ;      // 11
    print(--c) ;    // 11
    print(c) ;      // 11

    // RLop
    int d = 10 ;
    int* ptr ;
    ptr = &d ;
    print(d) ;
    print(ptr) ;
    print(*ptr) ;
    print(*&d) ;

    // Array
    int t[2] ;
    t[0] = 10 ;
    t[1] = 21 ;
    int i = 1;

    print(t[0]) ;
    print(t[1]) ;
    print(t[i]) ;

    return 0 ;
}