int f(){
    return 0 ;
}

int g(){
    f();
    return 2 ;
}

int args(int a, int b, int c){
    return a ;
}

int main(){

    f();
    g();

    // args(1,2,3);
    // args(1,2,3,4);

    return 0 ;
}
