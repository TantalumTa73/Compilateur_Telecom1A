int f(int x){
    return x+1 ;
}

int main(int x){
    int y ;
    y = f(f(42));
    print(f(f(10)));
    print(y);

    return 0;
}