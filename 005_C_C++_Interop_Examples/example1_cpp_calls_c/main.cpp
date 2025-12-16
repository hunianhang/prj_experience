#include <iostream>
#include "c_lib/math.h"

// extern "C"{
//     int add(int a, int b);
//     int subtract(int a, int b);
// }

int main()
{
    std::cout << "=== Example 1: C++ Calling C Functions ===" << std::endl;
    
    int result1 = add(10, 5);
    int result2 = subtract(10, 5);
    
    std::cout << "add(10, 5) = " << result1 << std::endl;
    std::cout << "subtract(10, 5) = " << result2 << std::endl;
    
    return 0;
}

