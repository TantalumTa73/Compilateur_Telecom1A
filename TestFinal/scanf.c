#include <stdio.h>
#include <stdlib.h>

char s[12] = "%d" ;
int a = 2938 ;

int main(){

    print_int(a);
    scanf(&s,&a) ;
    print_int(a);

    return 0 ;
}