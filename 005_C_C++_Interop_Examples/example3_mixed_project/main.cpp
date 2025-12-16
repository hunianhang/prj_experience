#include <iostream>
#include "c_code/math_utils.h"  // C library
#include "cpp_code/calculator.h" // C++ library with C interface

int main()
{
    std::cout << "=== Example 3: Mixed C/C++ Project ===" << std::endl;
    
    // Call C functions
    std::cout << "\n--- Calling C Functions ---" << std::endl;
    int c_result1 = add(10, 20);
    int c_result2 = multiply(5, 6);
    std::cout << "C add(10, 20) = " << c_result1 << std::endl;
    std::cout << "C multiply(5, 6) = " << c_result2 << std::endl;
    
    // Call C++ functions (wrapped with extern "C")
    std::cout << "\n--- Calling C++ Functions (via C interface) ---" << std::endl;
    int cpp_result1 = cpp_add(15, 25);
    int cpp_result2 = cpp_multiply(7, 8);
    std::cout << "C++ cpp_add(15, 25) = " << cpp_result1 << std::endl;
    std::cout << "C++ cpp_multiply(7, 8) = " << cpp_result2 << std::endl;
    
    // Use global object interface
    std::cout << "\n--- Using Global Object Interface ---" << std::endl;
    calculator_init();
    int global_result = calculator_add(100, 200);
    std::cout << "Global calculator_add(100, 200) = " << global_result << std::endl;
    calculator_cleanup();
    
    return 0;
}

