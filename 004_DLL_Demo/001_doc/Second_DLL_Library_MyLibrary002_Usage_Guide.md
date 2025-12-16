# Second DLL Library MyLibrary002 Usage Guide

> This document详细介绍 how to add and use the second DLL library `MyLibrary002` in the DLL_Demo project, and how to use multiple DLLs in a single application.

---

## I. Project Structure Overview

```
DLL_Demo/
├── MyLibrary/              # First DLL project (Math calculation library)
│   ├── MyLibrary.h
│   ├── MyLibrary.cpp
│   └── MyLibrary.vcxproj
├── MyLibrary002/           # Second DLL project (String utility library) ⭐ New
│   ├── MyLibrary002.h      # Export header file
│   ├── MyLibrary002.cpp    # Implementation file
│   ├── pch.h               # Precompiled header file
│   ├── pch.cpp
│   ├── framework.h
│   ├── dllmain.cpp
│   └── MyLibrary002.vcxproj
├── MyApp/                  # Console application (using both DLLs)
│   ├── main.cpp            # Main program demonstrating use of two DLLs
│   └── MyApp.vcxproj
├── DLL_Demo.sln            # Solution file (contains three projects)
└── x64/Debug/              # Output directory
    ├── MyLibrary.dll       # First DLL
    ├── MyLibrary.lib       # First DLL's import library
    ├── MyLibrary002.dll    # Second DLL ⭐ New
    ├── MyLibrary002.lib    # Second DLL's import library ⭐ New
    └── MyApp.exe           # Executable file
```

---

## II. MyLibrary002 Feature Overview

`MyLibrary002` is a **string utility library** that provides the following features:

### 2.1 C-Style Functions

- `GetLibraryName()` - Get library name
- `GetLibraryVersion()` - Get library version
- `GetStringLength()` - Get string length
- `ReverseString()` - Reverse a string
- `CompareStrings()` - Compare two strings

### 2.2 C++ Classes

#### StringUtility Class
- String operations: Set, Get, Append, Clear
- Case conversion: `ToUpperCase()`, `ToLowerCase()`
- Status queries: `IsEmpty()`, `GetLength()`

#### TextProcessor Class
- Text processing: `ProcessText()`, `RemoveWhitespace()`
- Formatting: `CapitalizeWords()`
- Statistics: `CountWords()`, `CountLines()`
- Configuration: `SetCaseSensitive()`, `IsCaseSensitive()`

### 2.3 Singleton Functions

- `GetStringUtilityInstance()` - Get StringUtility singleton
- `GetTextProcessorInstance()` - Get TextProcessor singleton

---

## III. MyLibrary002 Project Configuration

### 3.1 Export Macro Definition

Export macro is defined in `MyLibrary002.h`:

```cpp
#ifdef MYLIBRARY002_EXPORTS
#define MYLIBRARY002_API __declspec(dllexport)
#else
#define MYLIBRARY002_API __declspec(dllimport)
#endif
```

**Explanation**:
- When compiling DLL: Define `MYLIBRARY002_EXPORTS`, use `dllexport`
- When using DLL: Do not define this macro, use `dllimport`

### 3.2 Project Property Configuration

Already configured in `MyLibrary002.vcxproj`:

#### Preprocessor Definitions
```xml
<PreprocessorDefinitions>MYLIBRARY002_EXPORTS;_WINDOWS;_USRDLL;%(PreprocessorDefinitions)</PreprocessorDefinitions>
```

#### Output Directory
```xml
<OutDir>$(SolutionDir)$(Platform)\$(Configuration)\</OutDir>
```

**Setting in Visual Studio**:
1. Right-click `MyLibrary002` project → Properties
2. Configuration Properties → C/C++ → Preprocessor
3. Preprocessor Definitions: Ensure `MYLIBRARY002_EXPORTS` is included
4. Configuration Properties → General → Output Directory: `$(SolutionDir)$(Platform)\$(Configuration)\`

---

## IV. Using MyLibrary002 in MyApp

### 4.1 Include Header Files

In `MyApp/main.cpp`:

```cpp
#include "..\MyLibrary\MyLibrary.h"        // First DLL
#include "..\MyLibrary002\MyLibrary002.h"  // Second DLL ⭐ New
```

### 4.2 Configure Include Directories

In `MyApp.vcxproj`:

```xml
<AdditionalIncludeDirectories>
    $(ProjectDir)..\MyLibrary;
    $(ProjectDir)..\MyLibrary002;  ⭐ New
    %(AdditionalIncludeDirectories)
</AdditionalIncludeDirectories>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Properties
2. Configuration Properties → C/C++ → General
3. Additional Include Directories: Add `$(ProjectDir)..\MyLibrary002`

### 4.3 Configure Library Directories

Library directory configuration (same as first DLL):

```xml
<AdditionalLibraryDirectories>$(SolutionDir)$(Platform)\$(Configuration);%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
```

**Explanation**: Both DLLs' `.lib` files are in the same output directory, so no additional configuration is needed.

### 4.4 Link LIB Files

In `MyApp.vcxproj`:

```xml
<AdditionalDependencies>
    MyLibrary.lib;      # First DLL
    MyLibrary002.lib;   # Second DLL ⭐ New
    %(AdditionalDependencies)
</AdditionalDependencies>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Properties
2. Configuration Properties → Linker → Input
3. Additional Dependencies: Add `MyLibrary002.lib`

### 4.5 Add Project Reference (Recommended)

In `MyApp.vcxproj`:

```xml
<ItemGroup>
    <ProjectReference Include="..\MyLibrary\MyLibrary.vcxproj">
        <Project>{A1B2C3D4-E5F6-4A5B-8C9D-0E1F2A3B4C5D}</Project>
    </ProjectReference>
    <ProjectReference Include="..\MyLibrary002\MyLibrary002.vcxproj">  ⭐ New
        <Project>{86fb5154-c836-4c5d-8a05-d21842c32a1d}</Project>
    </ProjectReference>
</ItemGroup>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Add → Reference
2. Select `MyLibrary002` project
3. Click "OK"

**Advantages**:
- ✅ Automatically manages build order
- ✅ Automatically handles path configuration
- ✅ Easy to maintain

---

## V. Usage Examples

### 5.1 Using C-Style Functions

```cpp
#include "..\MyLibrary002\MyLibrary002.h"

// Get library information
const char* libName = GetLibraryName();
const char* libVersion = GetLibraryVersion();

// String operations
const char* testStr = "Hello World";
int length = GetStringLength(testStr);

char buffer[256];
strcpy_s(buffer, sizeof(buffer), testStr);
ReverseString(buffer, length);
```

### 5.2 Using C++ Classes (Direct Instantiation)

```cpp
// Using StringUtility class
StringUtility strUtil("Initial Value");
strUtil.Append(" - Appended");
strUtil.ToUpperCase();
const char* result = strUtil.GetString();

// Using TextProcessor class
TextProcessor textProc;
std::string processed = textProc.ProcessText("  hello world  ");
int wordCount = textProc.CountWords("hello world from dll");
```

### 5.3 Using Singleton Pattern

```cpp
// Get singleton instance
StringUtility& strUtil = GetStringUtilityInstance();
strUtil.SetString("Singleton String");

TextProcessor& textProc = GetTextProcessorInstance();
textProc.SetCaseSensitive(false);
```

### 5.4 Combining Both DLLs

```cpp
// Using Calculator from MyLibrary
Calculator calc;
int result = calc.Add(10, 20);

// Using StringUtility from MyLibrary002 to format result
StringUtility resultStr;
resultStr.SetString("Result: ");
resultStr.Append(std::to_string(result).c_str());
```

---

## VI. Solution File Configuration

### 6.1 Add Project to Solution

In `DLL_Demo.sln`:

```
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "MyLibrary", ...
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "MyLibrary002", ...  ⭐ New
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "MyApp", ...
```

### 6.2 Configure Platforms and Configurations

The solution file automatically adds all configurations (Debug/Release × x86/x64) for each project.

---

## VII. Build and Run

### 7.1 Build Order

Visual Studio automatically determines build order based on project references:

1. **MyLibrary** (First DLL)
2. **MyLibrary002** (Second DLL) ⭐ New
3. **MyApp** (Application)

### 7.2 Output Files

After building, the following files will be generated in `x64\Debug\`:

- `MyLibrary.dll` - First DLL
- `MyLibrary.lib` - First DLL's import library
- `MyLibrary.pdb` - First DLL's debug symbols
- `MyLibrary002.dll` - Second DLL ⭐ New
- `MyLibrary002.lib` - Second DLL's import library ⭐ New
- `MyLibrary002.pdb` - Second DLL's debug symbols ⭐ New
- `MyApp.exe` - Executable file
- `MyApp.pdb` - Application's debug symbols

### 7.3 Runtime DLL Paths

Ensure both DLL files are in one of the following locations:

1. **Application directory** (recommended): `x64\Debug\`
2. **System directory**: `C:\Windows\System32\` (64-bit)
3. **Directory in PATH environment variable**

---

## VIII. Configuration Checklist

### 8.1 MyLibrary002 Project Configuration

- [x] **Project Type**: Dynamic Library (.dll)
- [x] **Preprocessor Definitions**: `MYLIBRARY002_EXPORTS`
- [x] **Output Directory**: `$(SolutionDir)$(Platform)\$(Configuration)\`
- [x] **Header File**: Define `MYLIBRARY002_API` macro
- [x] **Implementation File**: Implement all exported functions and classes

### 8.2 MyApp Project Configuration (Using Both DLLs)

- [x] **Include Directories**:
  - `$(ProjectDir)..\MyLibrary`
  - `$(ProjectDir)..\MyLibrary002` ⭐ New
- [x] **Library Directories**: `$(SolutionDir)$(Platform)\$(Configuration)`
- [x] **Link Dependencies**:
  - `MyLibrary.lib`
  - `MyLibrary002.lib` ⭐ New
- [x] **Project References**:
  - `MyLibrary` project
  - `MyLibrary002` project ⭐ New

### 8.3 Solution Configuration

- [x] **Solution File**: Contains three projects
- [x] **Build Order**: DLL projects build before application
- [x] **Unified Output Directory**: All projects output to the same directory

---

## IX. Common Issues and Troubleshooting

### 9.1 Link Error: Unresolved MyLibrary002 Symbols

**Error Message**:
```
error LNK2019: unresolved external symbol "class StringUtility & __cdecl GetStringUtilityInstance(void)"
```

**Possible Causes**:
1. `MyLibrary002.lib` is not linked
2. LIB file path is incorrect
3. Function signature mismatch between header and implementation files

**Solutions**:
1. Check if `MyLibrary002.lib` is in "Additional Dependencies"
2. Check if "Additional Library Directories" path is correct
3. Verify that function signatures in header and implementation files match

### 9.2 Runtime Error: MyLibrary002.dll Not Found

**Error Message**:
```
System Error: The program can't start because MyLibrary002.dll is missing from your computer
```

**Solutions**:
1. Copy `MyLibrary002.dll` to the directory where `MyApp.exe` is located
2. Ensure both DLLs are in the same directory:
   - `MyLibrary.dll`
   - `MyLibrary002.dll`
   - `MyApp.exe`

### 9.3 Compilation Error: MyLibrary002.h Not Found

**Error Message**:
```
error C1083: Cannot open include file: "MyLibrary002.h"
```

**Solutions**:
1. Check if `$(ProjectDir)..\MyLibrary002` is added to "Additional Include Directories"
2. Check if the header file path is correct

---

## X. Comparison with First DLL

| Feature | MyLibrary | MyLibrary002 |
|------|-----------|--------------|
| **Functional Area** | Math calculation | String processing |
| **Export Macro** | `MYLIBRARY_API` | `MYLIBRARY002_API` |
| **Macro Condition** | `MYLIBRARY_EXPORTS` | `MYLIBRARY002_EXPORTS` |
| **Main Classes** | `Calculator` | `StringUtility`, `TextProcessor` |
| **C Functions** | `Add()`, `Multiply()` | `GetStringLength()`, `ReverseString()` |
| **Singleton Functions** | `GetCalculatorInstance()` | `GetStringUtilityInstance()`, `GetTextProcessorInstance()` |

---

## XI. Best Practices

### 11.1 Naming Conventions

- **Export Macro**: `<ProjectName>_API` (e.g., `MYLIBRARY002_API`)
- **Macro Condition**: `<ProjectName>_EXPORTS` (e.g., `MYLIBRARY002_EXPORTS`)
- **Consistency**: All DLLs use unified naming patterns

### 11.2 Functional Division

- **MyLibrary**: Focuses on math calculation functionality
- **MyLibrary002**: Focuses on string processing functionality
- **Separation of Concerns**: Each DLL is responsible for different functional areas

### 11.3 Path Management

- **Unified Output**: All DLLs output to the same directory
- **Use Macros**: `$(SolutionDir)`, `$(Platform)`, `$(Configuration)`
- **Relative Paths**: Avoid hardcoded absolute paths

### 11.4 Project References

- **Prefer Project References**: Instead of manually configuring paths
- **Automatic Build Order**: Ensures DLLs are built before the application
- **Easy Maintenance**: Automatically updates when paths change

---

## XII. Extension: Adding More DLLs

If you need to add a third, fourth DLL, follow the same pattern:

1. **Create New Project**: `MyLibrary003`
2. **Define Export Macro**: `MYLIBRARY003_API`, `MYLIBRARY003_EXPORTS`
3. **Configure Project**: Output directory, preprocessor definitions
4. **Update MyApp**:
   - Add include directories
   - Add link dependencies
   - Add project references
5. **Update Solution**: Add new project to `.sln` file

---

## XIII. Summary

### 13.1 Key Points

1. **Export Macro Pattern**: Each DLL uses independent export macros
2. **Project Configuration**: DLL projects define export macros, client projects do not
3. **Path Settings**:
   - **Include Directories**: Find all DLL header files
   - **Library Directories**: Find all DLL LIB files
   - **Link Dependencies**: Link all required LIB files
   - **Runtime Paths**: All DLL files are accessible
4. **Project References**: Recommended to use project references for automatic dependency management

### 13.2 Configuration Checklist

**Second DLL Project (MyLibrary002)**:
- [ ] Project Type: Dynamic Library
- [ ] Preprocessor Definitions: `MYLIBRARY002_EXPORTS`
- [ ] Output Directory: `$(SolutionDir)$(Platform)\$(Configuration)\`
- [ ] Header File: Define `MYLIBRARY002_API` macro

**Client Project (MyApp)**:
- [ ] Include Directories: Include all DLL header file directories
- [ ] Library Directories: Point to LIB file directory
- [ ] Link Dependencies: All required `.lib` files
- [ ] Project References: Reference all DLL projects
- [ ] Runtime Path: All DLL files are accessible

---

## XIV. Reference Resources

- [First DLL Usage Guide](./DLL_Usage_Guide_Based_on_DLL_Demo.md)
- [dllexport and dllimport Guide](../VerificationTestSystem/001_doc/dllexport和dllimport详解.md)
- [Microsoft Docs: Exporting from a DLL](https://docs.microsoft.com/en-us/cpp/build/exporting-from-a-dll)
- [Microsoft Docs: Importing into an Application](https://docs.microsoft.com/en-us/cpp/build/importing-into-an-application)

---

**Document Version**: 1.0  
**Last Updated**: 2025-12-15  
**Based on Project**: DLL_Demo (includes MyLibrary and MyLibrary002)

