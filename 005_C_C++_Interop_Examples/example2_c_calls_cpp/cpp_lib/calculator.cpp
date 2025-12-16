#include "calculator.h"

// C++ class (hidden from C)
class Calculator
{
public:
    int add(int a, int b) { return a + b; }
    int multiply(int a, int b) { return a * b; }
};

// C interface wrapper functions
extern "C" {
    void* calculator_create()
    {
        return new Calculator();
    }
    
    void calculator_destroy(void* handle)
    {
        if (handle != nullptr) {
            delete static_cast<Calculator*>(handle);
        }
    }
    
    int calculator_add(void* handle, int a, int b)
    {
        if (handle == nullptr) {
            return -1;  // Error
        }
        Calculator* calc = static_cast<Calculator*>(handle);
        return calc->add(a, b);
    }
    
    int calculator_multiply(void* handle, int a, int b)
    {
        if (handle == nullptr) {
            return -1;  // Error
        }
        Calculator* calc = static_cast<Calculator*>(handle);
        return calc->multiply(a, b);
    }
}

