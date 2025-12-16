//*******************************************************************************************************************
//**  main.cpp - Console Application Using Multiple DLLs
//**  Demonstrates how to import and use functions and classes from multiple DLL libraries
//********************************************************************************************************************

#include <iostream>
#include <string>
#include "..\MyLibrary\MyLibrary.h"
#include "..\MyLibrary002\MyLibrary002.h"

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "    Multiple DLL Usage Demo Program" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // ============================================================================
    // Part 1: Using MyLibrary (First DLL)
    // ============================================================================
    std::cout << "========== Part 1: MyLibrary (First DLL) ==========" << std::endl;
    std::cout << std::endl;

    // 1. Using C-style functions from MyLibrary
    std::cout << "1. Using C-style functions from MyLibrary:" << std::endl;
    std::cout << "   Version: " << GetVersion() << std::endl;
    
    int a = 10, b = 5;
    std::cout << "   Add(" << a << ", " << b << ") = " << Add(a, b) << std::endl;
    std::cout << "   Multiply(" << a << ", " << b << ") = " << Multiply(a, b) << std::endl;
    std::cout << std::endl;

    // 2. Using C++ class from MyLibrary (direct instantiation)
    std::cout << "2. Using Calculator class from MyLibrary (direct instantiation):" << std::endl;
    Calculator calc1;
    calc1.SetValue(100);
    std::cout << "   Created Calculator object, set value to: " << calc1.GetValue() << std::endl;
    std::cout << "   calc1.Add(20, 30) = " << calc1.Add(20, 30) << std::endl;
    std::cout << "   calc1.Subtract(50, 15) = " << calc1.Subtract(50, 15) << std::endl;
    std::cout << "   calc1.Multiply(6, 7) = " << calc1.Multiply(6, 7) << std::endl;
    std::cout << "   calc1.Divide(100.0, 3.0) = " << calc1.Divide(100.0, 3.0) << std::endl;
    std::cout << std::endl;

    // 3. Using singleton pattern from MyLibrary
    std::cout << "3. Using singleton pattern from MyLibrary:" << std::endl;
    Calculator& calc2 = GetCalculatorInstance();
    calc2.SetValue(200);
    std::cout << "   Got Calculator via singleton, set value to: " << calc2.GetValue() << std::endl;
    std::cout << "   calc2.Add(15, 25) = " << calc2.Add(15, 25) << std::endl;
    std::cout << std::endl;

    // ============================================================================
    // Part 2: Using MyLibrary002 (Second DLL)
    // ============================================================================
    std::cout << "========== Part 2: MyLibrary002 (Second DLL) ==========" << std::endl;
    std::cout << std::endl;

    // 1. Using C-style functions from MyLibrary002
    std::cout << "1. Using C-style functions from MyLibrary002:" << std::endl;
    std::cout << "   Library Name: " << GetLibraryName() << std::endl;
    std::cout << "   Library Version: " << GetLibraryVersion() << std::endl;
    
    const char* testStr = "Hello World";
    int strLen = GetStringLength(testStr);
    std::cout << "   String: \"" << testStr << "\"" << std::endl;
    std::cout << "   Length: " << strLen << std::endl;
    
    char reverseStr[256];
    #ifdef _WIN32
    strcpy_s(reverseStr, sizeof(reverseStr), testStr);
    #else
    strncpy(reverseStr, testStr, sizeof(reverseStr) - 1);
    reverseStr[sizeof(reverseStr) - 1] = '\0';
    #endif
    ReverseString(reverseStr, strLen);
    std::cout << "   Reversed: \"" << reverseStr << "\"" << std::endl;
    
    int compareResult = CompareStrings("Hello", "World");
    std::cout << "   Compare(\"Hello\", \"World\"): " << compareResult << std::endl;
    std::cout << std::endl;

    // 2. Using StringUtility class from MyLibrary002 (direct instantiation)
    std::cout << "2. Using StringUtility class from MyLibrary002 (direct instantiation):" << std::endl;
    StringUtility strUtil("Initial Value");
    std::cout << "   Created StringUtility with: \"" << strUtil.GetString() << "\"" << std::endl;
    std::cout << "   Length: " << strUtil.GetLength() << std::endl;
    
    strUtil.Append(" - Appended Text");
    std::cout << "   After append: \"" << strUtil.GetString() << "\"" << std::endl;
    
    strUtil.ToUpperCase();
    std::cout << "   ToUpperCase: \"" << strUtil.GetString() << "\"" << std::endl;
    
    strUtil.ToLowerCase();
    std::cout << "   ToLowerCase: \"" << strUtil.GetString() << "\"" << std::endl;
    std::cout << std::endl;

    // 3. Using TextProcessor class from MyLibrary002
    std::cout << "3. Using TextProcessor class from MyLibrary002:" << std::endl;
    TextProcessor textProc;
    std::string inputText = "  hello world from dll  ";
    std::cout << "   Input: \"" << inputText << "\"" << std::endl;
    
    std::string processed = textProc.ProcessText(inputText);
    std::cout << "   Processed: \"" << processed << "\"" << std::endl;
    
    std::string noWhitespace = textProc.RemoveWhitespace(inputText);
    std::cout << "   RemoveWhitespace: \"" << noWhitespace << "\"" << std::endl;
    
    std::string capitalized = textProc.CapitalizeWords("hello world from dll");
    std::cout << "   CapitalizeWords: \"" << capitalized << "\"" << std::endl;
    
    int wordCount = textProc.CountWords("hello world from dll");
    std::cout << "   CountWords: " << wordCount << std::endl;
    
    std::string multiLine = "Line 1\nLine 2\nLine 3";
    int lineCount = textProc.CountLines(multiLine);
    std::cout << "   CountLines (for \"" << multiLine << "\"): " << lineCount << std::endl;
    std::cout << std::endl;

    // 4. Using singleton pattern from MyLibrary002
    std::cout << "4. Using singleton pattern from MyLibrary002:" << std::endl;
    StringUtility& strUtilSingleton = GetStringUtilityInstance();
    strUtilSingleton.SetString("Singleton String");
    std::cout << "   Singleton StringUtility: \"" << strUtilSingleton.GetString() << "\"" << std::endl;
    
    TextProcessor& textProcSingleton = GetTextProcessorInstance();
    textProcSingleton.SetCaseSensitive(false);
    std::cout << "   Singleton TextProcessor case sensitive: " 
              << (textProcSingleton.IsCaseSensitive() ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // ============================================================================
    // Part 3: Combining both DLLs
    // ============================================================================
    std::cout << "========== Part 3: Combining Both DLLs ==========" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Combining Calculator from MyLibrary and StringUtility from MyLibrary002:" << std::endl;
    Calculator combinedCalc;
    int result1 = combinedCalc.Add(10, 20);
    int result2 = combinedCalc.Multiply(5, 6);
    
    StringUtility resultStr;
    resultStr.SetString("Result: ");
    resultStr.Append(std::to_string(result1).c_str());
    resultStr.Append(" + ");
    resultStr.Append(std::to_string(result2).c_str());
    resultStr.Append(" = ");
    resultStr.Append(std::to_string(result1 + result2).c_str());
    
    std::cout << "   " << resultStr.GetString() << std::endl;
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "Demo completed! Press any key to exit..." << std::endl;
    std::cin.get();

    return 0;
}

