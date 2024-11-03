#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bool.h>


void complexFunction(int num) {

    int a = 1 ;
    bool b = true ;
    char c = 'a' ;
    char* d = "abcd" ;

    int t[] = 1 ;
    int t[] = {1,2,3,4,5} ;

    for (int i = 0; i < num; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < i; j++) {
                if (j % 3 == 0) {
                    // printf("i: %d, j: %d - Divisible by 3\n", i, j);
                    print_int(0);
                } else {
                    // printf("i: %d, j: %d - Not divisible by 3\n", i, j);
                    print_int(1);
                }
            }
        } else {
            int k = 0;
            while (k < i) {
                if (k % 2 == 0) {
                    // printf("i: %d, k: %d - Even\n", i, k);
                    print_int()
                } else {
                    // printf("i: %d, k: %d - Odd\n", i, k);
                }
                k++;
            }
        }
    }
}
