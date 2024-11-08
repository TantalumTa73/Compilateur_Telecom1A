#include <stdbool.h>

int main() {
   
    int result;

    // Test 1: Basic boolean values assigned from integers
    bool a = 1;       // true
    bool b = 0;       // false
    print_int(a == true);   // Expected: 1
    print_int(b == false);  // Expected: 1

    // Test 2: Boolean NOT
    result = !a;
    print_int(result);      // Expected: 0
    result = !b;
    print_int(result);      // Expected: 1

    // Test 3: Boolean AND (&&)
    result = a && 1;        // true && true
    print_int(result);      // Expected: 1
    result = a && b;        // true && false
    print_int(result);      // Expected: 0

    // Test 4: Boolean OR (||)
    result = a || b;        // true || false
    print_int(result);      // Expected: 1
    result = b || 0;        // false || false
    print_int(result);      // Expected: 0

    // Test 5: Integer to boolean assignment
    int c = 5;
    bool d = c;             // Any non-zero integer is true
    print_int(d);           // Expected: 1

    int e = 0;
    bool f = e;             // Zero is false
    print_int(f);           // Expected: 0

    // Test 6: Boolean to integer assignment
    int g = a;              // true -> 1
    int h = b;              // false -> 0
    print_int(g);           // Expected: 1
    print_int(h);           // Expected: 0

    // Test 7: Mixed boolean expressions with integer assignments
    result = a && c;        // true && 5 (non-zero)
    print_int(result);      // Expected: 1
    result = b || e;        // false || 0
    print_int(result);      // Expected: 0

    // Test 8: Complex expressions
    result = (a || b) && !e;    // (true || false) && true
    print_int(result);          // Expected: 1

    result = (b && c) || (f || a); // (false && true) || (false || true)
    print_int(result);          // Expected: 1

    return 0;


}