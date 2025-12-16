#include <stdio.h>
#include "cpp_lib/calculator.h"

int main()
{
    printf("=== Example 2: C Calling C++ Functions ===\n");
    
    // Create C++ object
    void* calc = calculator_create();
    
    if (calc == NULL) {
        printf("Error: Failed to create calculator\n");
        return 1;
    }
    
    // Use C++ object through C interface
    int sum = calculator_add(calc, 10, 20);
    int product = calculator_multiply(calc, 5, 6);
    
    printf("calculator_add(10, 20) = %d\n", sum);
    printf("calculator_multiply(5, 6) = %d\n", product);
    
    // Destroy C++ object
    calculator_destroy(calc);
    
    return 0;
}

