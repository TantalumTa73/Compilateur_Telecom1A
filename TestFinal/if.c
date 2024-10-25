// int x = 1;
int main(){
    // print(x);
    // x=2;
    // print(x);

    // int a = 0;
    // int t[2] ;
    // t[0] = 1 ;
    // t[1] = 2 ;

    // print(a) ;
    // print(t[0]) ;
    // print(t[1]) ;

    /////////////////////////
    //        valid        //
    /////////////////////////

    print(15 + 5); // 20
    print(15 - 5); // 10
    print(15 * 5); // 75
    print(15 / 7); // 2
    print(15 % 7); // 1

    print(-7); // -7
    print(!7); // 0
    print(~7); // -8

    print(11 & 13); // 9
    print(11 | 13); // 15
    print(11 ^ 13); // 4

    print(11 << 1); // 22
    print(11 >> 1); // 5
    
    // print(0 ? 10 : 20);  // 10
    // print(1 ? 10 : 20);  // 20


    int a = 10 ;
    print(a);        // 10
    print(++a);      // 11
    print(a);        // 11
    print(a++);      // 11
    print(a);        // 12

    int b = 20 ;
    print(b);        // 20
    b = 13 ;
    print(b);        // 13
    b += 2 ;
    print(b);        // 15

    // int x1 ;
    // int x2 ;
    // x1 = 30 ;
    // x2 = 40 ;
    // print(*(&x1));       // 30
    // print(*(&x2-8));     // 40

   
    return 0 ;
}

/*
TODO:
- global variables initialization
- automatic test system
- operators >> <<
- array alloc
- array access
- left value get, ValGet VarGet ArrayGet
- keyword break continue const auto inline struct (lexer.ml)
- multiple declaration in one line
- the comma operator

TO CHECK:
- multiple declaration with initialization


LIST OF OP:

- LLop      L -> L
    - x[y]
    - ++x
- RLop      E -> L
    - *x

- LLop | RRop
    - x.y
    - x->y

- LRop      L -> E
    - x++
    - &x


- uniop : E -> E
- binop : E*E -> E
- assingop : L*E -> ()
- ternop : E*E*E -> E
           E*L*L -> L
- call : L * E^n -> E


*/