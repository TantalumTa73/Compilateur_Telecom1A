int tab[100];

int main(){
    for (int i = 0; i < 100; i ++){
        tab[i] = i;
    }
    for (int i = 0; i < 100; i ++){
        print_int(tab[i]);
    }
    return 0;
}