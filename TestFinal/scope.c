
// int test1() {
//     int x;
//     int y;
//     x = 1;
//     y = 1;
//     {
//         int y;
//         x = 2;
//         y = 2;
//     }
//     // Should print 2 and 1
//     print(x);
//     print(y);
// }

int test2() {
    int a = 5;
    {
        int a = 10;
        {
            int a = 15;
            print(a); // Should print 15
        }
        print(a); // Should print 10
    }
    print(a); // Should print 5
}

// int test3() {
//     int b = 20;
//     {
//         int b = 25;
//         {
//             b = 30;
//             print(b); // Should print 30
//         }
//         print(b); // Should print 30
//     }
//     print(b); // Should print 20
// }

int main() {
    // test1();
    test2();
    // test3();
    return 0;
}