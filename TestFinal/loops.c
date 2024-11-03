int main(){

    for (int i = 0 ; i < 20 ; i++){
        if (i == 10) break ;
        if (i%2) continue ;
        print_int(i);
    }

    int j = 0 ;
    while (j++ < 20){
        if (j == 10) break ;
        if (j%2) continue ;
        print_int(j);
    }

    return 0 ;
}