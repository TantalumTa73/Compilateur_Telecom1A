int main(){

    print_int(15 + 5); // 20
    print_int(15 - 5); // 10
    print_int(15 * 5); // 75
    print_int(15 / 7); // 2
    print_int(15 % 7); // 1

    print_int(-7); // -7
    print_int(!7); // 0
    print_int(~7); // -8

    print_int(11 & 13); // 9
    print_int(11 | 13); // 15
    print_int(11 ^ 13); // 4

    print_int(11 << 1); // 22
    print_int(11 >> 1); // 5
    
    print_int(0 ? 10 : 20);  // 10
    print_int(1 ? 10 : 20);  // 20

    return 0 ;
}