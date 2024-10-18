int u ;
int x ;
int y ;
int z ;

int f ( int a ) {
    int u ;
    u = a + 2 ;
    return 3 * u + 8;
}

int main ( int a ) {

    --a ;
    a = 1 + a++ ;

    a[1] = 1;
    a[1][2] = 1;

    a = 15 * -5;
    print(a);
    
    a = 5 + 5 / 5;
    print(a);

    a = 1 + 1 + 1 + 1 + 1 + 1;
    print(a);

    a = 1 - 1;
    print(a);

    a = -1 - 1;
    print(a);

    a = -1 + (-1) * 3;
    print(a);

    a = 15 / (3 * 5);
    print(a);

    a = 15 / 3 * 5;
    print(a);

    a = -5 / 5;
    print(a);

    a = (1);
    print(a);

    a = 18 / (3 + 3 + 1 - 1);
    print(a);

    a = 15 / (-3) + 2;
    print(a);

    a = -a + 5;
    print(a);

    a = 3 - 2;
    print(a);

    a = (3 - 2);
    print(a);

    a = 7 - 3 * 2;
    print(a);

    a = 1 - a;
    print(a);

    a = -1 - 2 - 3 - 4;
    print(a);

    a = 7 + (-3);
    print(a);

    a = a - a;
    print(a);

    a = -5;
    print(a);

    a = 5 - 5 - 5 - 5 * (-1);
    print(a);

    return f(3);

}
