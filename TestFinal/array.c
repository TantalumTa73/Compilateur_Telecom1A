int main(){

    // int a[10] ;
    // a[0] = 10;
    // a[3] = 20;
    // print_int( a[0] ) ;
    // print_int( a[3] ) ;
    int i ;
    int j ;

    int t[10][10] ;
    // var def t {80, 8}
    // --> ctx[main].push_var t {80, 8}

    // array_size 80 8
    // t[i][j] = t + i*80 + j*8
    // t[0][0] = 1;
    // t[1][1] = 11;
    // t[4][6] = 46;

    t[i][j] ;

    // print_int(t[0][0]);
    // print_int(t[1][1]);
    // print_int(t[4][6]);


    // int* s = malloc(10*4) ;
    // s[0] = 102;
    // s[5] = 1010;
    // print_int(s[0]);
    // print_int(s[5]);

    /*
    int t[N1][N2][N3] ;
    t[i][j][k] : t + i*N2*N3*8 + j*N3*8 + k*8

    int t[N1][N2] ;
    t[i][j] : t + i*N2*8 + j*8
    t
        [i] -> N2*8
        [j] -> 8

    (++(t[i]))[j]


    int t[N1][N2] ;
    (++t[i])[j]


    array get
        op ++x
            array get
                var get
                    t
                i
        j
    left_val::array_size 

    */

    return 0 ;
}