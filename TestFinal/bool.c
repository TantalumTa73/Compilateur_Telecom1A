bool funcTrue() {
    return 1;
}

bool funcFalse() {
    return 0;
}

int main() {
    int a = 1;
	int b = 0;
	int c = 1;
    int result;

    // Test 1: Basic boolean operations
    result = (a && b) || (c && !b);
    print_int(result); // Expected: 1

    // Test 2: Precedence and associativity
    result = a || b && c;
    print_int(result); // Expected: 1 (&& has higher precedence than ||)

    // Test 3: Short-circuit evaluation
    result = a || funcFalse();
    print_int(result); // Expected: 1, funcFalse should not be called

    result = b && funcTrue();
    print_int(result); // Expected: 0, funcTrue should not be called

    // Test 4: Complex expression with mixed operators
    result = (a && (b || c)) && (!a || (b && c));
    print_int(result); // Expected: 0

    // Test 5: Edge cases with negation and double negation
    result = !!a && !b;
    print_int(result); // Expected: 1

    // Test 6: Nested boolean expressions
    result = (a || (b && (c || !a))) && (b || (!c && a));
    print_int(result); // Expected: 0

    return 0;
}