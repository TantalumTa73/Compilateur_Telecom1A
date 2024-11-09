int f(int a, int b){
    return a + b;
}

int g(){
    print_int(f(40, 2));
    return 2 ;
}

// int args(int a, int b, int c){
//     return a ;
// }

int main(){

    g();

    // args(1,2,3);
    // args(1,2,3,4);

    return 0 ;
}
