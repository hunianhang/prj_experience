//*******************************************************************************************************************
//**  MyLibrary.h - DLL Export Header File
//**  Demonstrates how to use __declspec(dllexport/dllimport) to export and import DLL symbols
//********************************************************************************************************************

#pragma once
#ifndef MYLIBRARY_H
#define MYLIBRARY_H

// Define export macro
// When compiling the DLL project, MYLIBRARY_EXPORTS is defined, so MYLIBRARY_API becomes __declspec(dllexport)
// When a project using the DLL includes this header, MYLIBRARY_API becomes __declspec(dllimport)
#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

// Export C-style functions
extern "C" {
    // Simple math function examples
    MYLIBRARY_API int Add(int a, int b);
    MYLIBRARY_API int Multiply(int a, int b);
    MYLIBRARY_API const char* GetVersion();
}

// Export C++ class
class MYLIBRARY_API Calculator
{
public:
    Calculator();
    ~Calculator();
    
    int Add(int a, int b);
    int Subtract(int a, int b);
    int Multiply(int a, int b);
    double Divide(double a, double b);
    
    void SetValue(int value);
    int GetValue() const;
    
private:
    int m_value;
};

// Export singleton function (similar to VerificationSystemInstance)
MYLIBRARY_API Calculator& GetCalculatorInstance();

#endif // MYLIBRARY_H

