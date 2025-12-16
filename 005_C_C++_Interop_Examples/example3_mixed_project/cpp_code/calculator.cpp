#include "calculator.h"
#include <iostream>

// C++ class implementation
class Calculator
{
public:
    int add(int a, int b) {
        return a + b;
    }
    
    int multiply(int a, int b) {
        return a * b;
    }
};

// C++ functions (can be called from C)
extern "C" int cpp_add(int a, int b)
{
    Calculator calc;
    return calc.add(a, b);
}

extern "C" int cpp_multiply(int a, int b)
{
    Calculator calc;
    return calc.multiply(a, b);
}

// More complex example: Using global object
static Calculator* g_calculator = nullptr;

extern "C" void calculator_init()
{
    if (g_calculator == nullptr) {
        g_calculator = new Calculator();
    }
}

extern "C" void calculator_cleanup()
{
    if (g_calculator != nullptr) {
        delete g_calculator;
        g_calculator = nullptr;
    }
}

extern "C" int calculator_add(int a, int b)
{
    if (g_calculator == nullptr) {
        return -1;  // Error
    }
    return g_calculator->add(a, b);
}

