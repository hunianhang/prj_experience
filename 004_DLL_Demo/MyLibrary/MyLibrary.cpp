//*******************************************************************************************************************
//**  MyLibrary.cpp - DLL Implementation File
//**  Implements all functions and classes declared in the header file
//********************************************************************************************************************

#include "MyLibrary.h"
#include <iostream>

// ============================================================================
// C-style function implementations
// ============================================================================

extern "C" {
    MYLIBRARY_API int Add(int a, int b)
    {
        return a + b;
    }

    MYLIBRARY_API int Multiply(int a, int b)
    {
        return a * b;
    }

    MYLIBRARY_API const char* GetVersion()
    {
        return "MyLibrary v1.0.0";
    }
}

// ============================================================================
// C++ class implementations
// ============================================================================

Calculator::Calculator() : m_value(0)
{
    std::cout << "[MyLibrary] Calculator object created" << std::endl;
}

Calculator::~Calculator()
{
    std::cout << "[MyLibrary] Calculator object destroyed" << std::endl;
}

int Calculator::Add(int a, int b)
{
    return a + b;
}

int Calculator::Subtract(int a, int b)
{
    return a - b;
}

int Calculator::Multiply(int a, int b)
{
    return a * b;
}

double Calculator::Divide(double a, double b)
{
    if (b == 0.0) {
        std::cout << "[MyLibrary] Warning: Division by zero!" << std::endl;
        return 0.0;
    }
    return a / b;
}

void Calculator::SetValue(int value)
{
    m_value = value;
}

int Calculator::GetValue() const
{
    return m_value;
}

// ============================================================================
// Singleton function implementation (similar to VerificationSystemInstance)
// ============================================================================

MYLIBRARY_API Calculator& GetCalculatorInstance()
{
    static Calculator* instance = new Calculator();
    return *instance;
}

