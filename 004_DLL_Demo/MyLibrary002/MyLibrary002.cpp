//*******************************************************************************************************************
//**  MyLibrary002.cpp - Second DLL Implementation File
//**  Implements all functions and classes declared in MyLibrary002.h
//********************************************************************************************************************

#include "pch.h"
#include "MyLibrary002.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <cctype>

// ============================================================================
// C-style function implementations
// ============================================================================

extern "C" {
    MYLIBRARY002_API const char* GetLibraryName()
    {
        return "MyLibrary002 - String Utility Library";
    }

    MYLIBRARY002_API const char* GetLibraryVersion()
    {
        return "MyLibrary002 v2.0.0";
    }

    MYLIBRARY002_API int GetStringLength(const char* str)
    {
        if (str == nullptr)
            return 0;
        return static_cast<int>(strlen(str));
    }

    MYLIBRARY002_API void ReverseString(char* str, int length)
    {
        if (str == nullptr || length <= 0)
            return;
        
        char* start = str;
        char* end = str + length - 1;
        
        while (start < end)
        {
            char temp = *start;
            *start = *end;
            *end = temp;
            start++;
            end--;
        }
    }

    MYLIBRARY002_API int CompareStrings(const char* str1, const char* str2)
    {
        if (str1 == nullptr && str2 == nullptr)
            return 0;
        if (str1 == nullptr)
            return -1;
        if (str2 == nullptr)
            return 1;
        
        return strcmp(str1, str2);
    }
}

// ============================================================================
// StringUtility class implementation
// ============================================================================

StringUtility::StringUtility() : m_buffer(nullptr), m_capacity(0), m_length(0)
{
    Resize(16); // Initial capacity
    m_buffer[0] = '\0';
    std::cout << "[MyLibrary002] StringUtility object created" << std::endl;
}

StringUtility::StringUtility(const char* initialValue) : m_buffer(nullptr), m_capacity(0), m_length(0)
{
    if (initialValue != nullptr)
    {
        m_length = static_cast<int>(strlen(initialValue));
        Resize(m_length + 1);
        strcpy_s(m_buffer, m_capacity, initialValue);
    }
    else
    {
        Resize(16);
        m_buffer[0] = '\0';
    }
    std::cout << "[MyLibrary002] StringUtility object created with initial value" << std::endl;
}

StringUtility::~StringUtility()
{
    if (m_buffer != nullptr)
    {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
    std::cout << "[MyLibrary002] StringUtility object destroyed" << std::endl;
}

void StringUtility::SetString(const char* str)
{
    if (str == nullptr)
    {
        Clear();
        return;
    }
    
    int newLength = static_cast<int>(strlen(str));
    if (newLength >= m_capacity)
    {
        Resize(newLength + 1);
    }
    
    #ifdef _WIN32
    strcpy_s(m_buffer, m_capacity, str);
    #else
    strncpy(m_buffer, str, m_capacity - 1);
    m_buffer[m_capacity - 1] = '\0';
    #endif
    m_length = newLength;
}

const char* StringUtility::GetString() const
{
    return (m_buffer != nullptr) ? m_buffer : "";
}

int StringUtility::GetLength() const
{
    return m_length;
}

void StringUtility::Append(const char* str)
{
    if (str == nullptr)
        return;
    
    int strLen = static_cast<int>(strlen(str));
    int newLength = m_length + strLen;
    
    if (newLength >= m_capacity)
    {
        Resize(newLength + 1);
    }
    
    #ifdef _WIN32
    strcat_s(m_buffer, m_capacity, str);
    #else
    strncat(m_buffer, str, m_capacity - m_length - 1);
    m_buffer[m_capacity - 1] = '\0';
    #endif
    m_length = newLength;
}

void StringUtility::Clear()
{
    if (m_buffer != nullptr)
    {
        m_buffer[0] = '\0';
        m_length = 0;
    }
}

void StringUtility::ToUpperCase()
{
    if (m_buffer == nullptr)
        return;
    
    for (int i = 0; i < m_length; i++)
    {
        m_buffer[i] = static_cast<char>(toupper(static_cast<unsigned char>(m_buffer[i])));
    }
}

void StringUtility::ToLowerCase()
{
    if (m_buffer == nullptr)
        return;
    
    for (int i = 0; i < m_length; i++)
    {
        m_buffer[i] = static_cast<char>(tolower(static_cast<unsigned char>(m_buffer[i])));
    }
}

bool StringUtility::IsEmpty() const
{
    return (m_length == 0);
}

void StringUtility::Resize(int newCapacity)
{
    if (newCapacity <= 0)
        newCapacity = 16;
    
    char* newBuffer = new char[newCapacity];
    newBuffer[0] = '\0';
    
    if (m_buffer != nullptr)
    {
        if (m_length > 0)
        {
            #ifdef _WIN32
            strcpy_s(newBuffer, newCapacity, m_buffer);
            #else
            strncpy(newBuffer, m_buffer, newCapacity - 1);
            newBuffer[newCapacity - 1] = '\0';
            #endif
        }
        delete[] m_buffer;
    }
    
    m_buffer = newBuffer;
    m_capacity = newCapacity;
}

// ============================================================================
// TextProcessor class implementation
// ============================================================================

TextProcessor::TextProcessor() : m_caseSensitive(true)
{
    std::cout << "[MyLibrary002] TextProcessor object created" << std::endl;
}

TextProcessor::~TextProcessor()
{
    std::cout << "[MyLibrary002] TextProcessor object destroyed" << std::endl;
}

std::string TextProcessor::ProcessText(const std::string& input)
{
    std::string result = input;
    // Remove leading and trailing whitespace
    size_t start = result.find_first_not_of(" \t\n\r");
    if (start != std::string::npos)
    {
        result = result.substr(start);
    }
    size_t end = result.find_last_not_of(" \t\n\r");
    if (end != std::string::npos)
    {
        result = result.substr(0, end + 1);
    }
    return result;
}

std::string TextProcessor::RemoveWhitespace(const std::string& input)
{
    std::string result;
    result.reserve(input.length());
    
    for (char c : input)
    {
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            result += c;
        }
    }
    
    return result;
}

std::string TextProcessor::CapitalizeWords(const std::string& input)
{
    std::string result = input;
    bool newWord = true;
    
    for (size_t i = 0; i < result.length(); i++)
    {
        if (std::isspace(static_cast<unsigned char>(result[i])))
        {
            newWord = true;
        }
        else if (newWord)
        {
            result[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[i])));
            newWord = false;
        }
        else
        {
            result[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(result[i])));
        }
    }
    
    return result;
}

int TextProcessor::CountWords(const std::string& input)
{
    if (input.empty())
        return 0;
    
    std::istringstream iss(input);
    std::string word;
    int count = 0;
    
    while (iss >> word)
    {
        count++;
    }
    
    return count;
}

int TextProcessor::CountLines(const std::string& input)
{
    if (input.empty())
        return 0;
    
    int count = 1; // At least one line
    for (char c : input)
    {
        if (c == '\n')
        {
            count++;
        }
    }
    
    return count;
}

void TextProcessor::SetCaseSensitive(bool sensitive)
{
    m_caseSensitive = sensitive;
}

bool TextProcessor::IsCaseSensitive() const
{
    return m_caseSensitive;
}

// ============================================================================
// Singleton function implementations
// ============================================================================

MYLIBRARY002_API StringUtility& GetStringUtilityInstance()
{
    static StringUtility* instance = new StringUtility();
    return *instance;
}

MYLIBRARY002_API TextProcessor& GetTextProcessorInstance()
{
    static TextProcessor* instance = new TextProcessor();
    return *instance;
}

