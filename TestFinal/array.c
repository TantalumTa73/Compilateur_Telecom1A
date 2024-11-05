int main(){

    int a[10] ;
    a[0] = 10;
    a[3] = 20;
    print_int( a[0] ) ;
    print_int( a[3] ) ;

    int t[10][10] ;
    t[0][0] = 1;
    t[1][1] = 11;
    t[4][6] = 46;

    print_int(t[0][0]);
    print_int(t[1][1]);
    print_int(t[4][6]);
    /*
    int t[N1][N2][N3] ;
    t[i][j][k] : t + i*N2*N3*8 + j*N3*8 + k*8
    
    */

    return 0 ;
}