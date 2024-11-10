void f_add(int* a){
    *a += 1;
}

int main() {
    int a = 41;
    f_add(&a); 
    print_int(a);
}