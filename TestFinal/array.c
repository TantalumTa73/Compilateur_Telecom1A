int main(){
    int tab[10];
    int t = 420;
    for (int i = 41; i < 43; i ++){
        print_int(i);
    }
    for (int i = 0; i < 2; i ++){
        print_int(t + i);
    }
    for (int i = 0; i < 10; i ++){
        tab[i] = i;
    }
    for (int i = 0; i < 10; i ++){
        print_int(tab[i]);
    }
        return 0;
}