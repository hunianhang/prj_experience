//*******************************************************************************************************************
//**  MyLibrary002.h - Second DLL Export Header File
//**  Demonstrates how to create and use a second DLL library
//**  This library provides string manipulation and utility functions
//********************************************************************************************************************

#pragma once
#ifndef MYLIBRARY002_H
#define MYLIBRARY002_H

// Define export macro for MyLibrary002
// When compiling the DLL project, MYLIBRARY002_EXPORTS is defined, so MYLIBRARY002_API becomes __declspec(dllexport)
// When a project using the DLL includes this header, MYLIBRARY002_API becomes __declspec(dllimport)
#ifdef MYLIBRARY002_EXPORTS
#define MYLIBRARY002_API __declspec(dllexport)
#else
#define MYLIBRARY002_API __declspec(dllimport)
#endif

#include <string>

// ============================================================================
// C-style function exports
// ============================================================================

extern "C" {
    // String manipulation functions
    MYLIBRARY002_API const char* GetLibraryName();
    MYLIBRARY002_API const char* GetLibraryVersion();
    MYLIBRARY002_API int GetStringLength(const char* str);
    MYLIBRARY002_API void ReverseString(char* str, int length);
    MYLIBRARY002_API int CompareStrings(const char* str1, const char* str2);
}

// ============================================================================
// C++ class exports
// ============================================================================

// String utility class
class MYLIBRARY002_API StringUtility
{
public:
    StringUtility();
    explicit StringUtility(const char* initialValue);
    ~StringUtility();
    
    // String operations
    void SetString(const char* str);
    const char* GetString() const;
    int GetLength() const;
    void Append(const char* str);
    void Clear();
    
    // Utility functions
    void ToUpperCase();
    void ToLowerCase();
    bool IsEmpty() const;
    
private:
    char* m_buffer;
    int m_capacity;
    int m_length;
    
    void Resize(int newCapacity);
};

// Text processor class
class MYLIBRARY002_API TextProcessor
{
public:
    TextProcessor();
    ~TextProcessor();
    
    // Text processing functions
    std::string ProcessText(const std::string& input);
    std::string RemoveWhitespace(const std::string& input);
    std::string CapitalizeWords(const std::string& input);
    int CountWords(const std::string& input);
    int CountLines(const std::string& input);
    
    // Configuration
    void SetCaseSensitive(bool sensitive);
    bool IsCaseSensitive() const;
    
private:
    bool m_caseSensitive;
};

// ============================================================================
// Singleton function export (similar to VerificationSystemInstance)
// ============================================================================

MYLIBRARY002_API StringUtility& GetStringUtilityInstance();
MYLIBRARY002_API TextProcessor& GetTextProcessorInstance();

#endif // MYLIBRARY002_H

