# DLL Usage Guide - Based on DLL_Demo Project

> This document uses the `DLL_Demo` project as an example to详细介绍 how to use `dllexport` and `dllimport`, and how to configure DLL and LIB file paths.

---

## I. Project Structure Overview

```
DLL_Demo/
├── MyLibrary/              # DLL project (provider)
│   ├── MyLibrary.h         # Export header file (defines export macro)
│   ├── MyLibrary.cpp       # DLL implementation file
│   └── MyLibrary.vcxproj   # Visual Studio project file
├── MyApp/                  # Console application (consumer)
│   ├── main.cpp            # Main program demonstrating DLL usage
│   └── MyApp.vcxproj       # Visual Studio project file
├── DLL_Demo.sln            # Visual Studio solution file
└── x64/Debug/              # Output directory
    ├── MyLibrary.dll       # Dynamic link library
    ├── MyLibrary.lib       # Import library (used during linking)
    └── MyApp.exe           # Executable file
```

---

## II. Core Concepts: `dllexport` and `dllimport`

### 2.1 Export Macro Definition

The standard export/import macro is defined in `MyLibrary.h`:

```13:17:MyLibrary/MyLibrary.h
#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif
```

**How It Works**:

1. **When compiling the DLL project** (`MyLibrary`):
   - The `MYLIBRARY_EXPORTS` macro is defined in project settings
   - `MYLIBRARY_API` expands to `__declspec(dllexport)`
   - Marks symbols (functions, classes, variables) to be exported

2. **In projects using the DLL** (`MyApp`):
   - The `MYLIBRARY_EXPORTS` macro is **not** defined
   - `MYLIBRARY_API` expands to `__declspec(dllimport)`
   - Tells the linker that these symbols need to be imported from the DLL

### 2.2 Why This Pattern?

- ✅ **Single header file**: The same header file can be used for both DLL and client
- ✅ **Automatic switching**: Automatically chooses export or import based on compilation context
- ✅ **Performance optimization**: Using `dllimport` provides better call performance
- ✅ **Standard practice**: This is the standard pattern for Windows DLL development

---

## III. DLL Project Configuration (MyLibrary)

### 3.1 Project Type Setting

In `MyLibrary.vcxproj`, the project type is set to dynamic library:

```30:30:MyLibrary/MyLibrary.vcxproj
    <ConfigurationType>DynamicLibrary</ConfigurationType>
```

**Setting in Visual Studio**:
1. Right-click project → Properties
2. Configuration Properties → General
3. Configuration Type: Select **"Dynamic Library (.dll)"**

### 3.2 Define Export Macro

Define the `MYLIBRARY_EXPORTS` macro in project properties:

```97:97:MyLibrary/MyLibrary.vcxproj
      <PreprocessorDefinitions>WIN32;_DEBUG;MYLIBRARY_EXPORTS;_WINDOWS;_USRDLL;%(PreprocessorDefinitions)</PreprocessorDefinitions>
```

**Setting in Visual Studio**:
1. Right-click `MyLibrary` project → Properties
2. Configuration Properties → C/C++ → Preprocessor
3. Preprocessor Definitions: Add `MYLIBRARY_EXPORTS`

**Or directly edit the `.vcxproj` file**:
```xml
<PreprocessorDefinitions>MYLIBRARY_EXPORTS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
```

### 3.3 Output File Location

```85:86:MyLibrary/MyLibrary.vcxproj
    <OutDir>$(SolutionDir)$(Platform)\$(Configuration)\</OutDir>
    <IntDir>$(Platform)\$(Configuration)\</IntDir>
```

**Output Files**:
- **DLL file**: `x64\Debug\MyLibrary.dll` (required at runtime)
- **LIB file**: `x64\Debug\MyLibrary.lib` (required during linking)
- **PDB file**: `x64\Debug\MyLibrary.pdb` (debug symbols)

**Setting in Visual Studio**:
1. Right-click project → Properties
2. Configuration Properties → General
3. Output Directory: `$(SolutionDir)$(Platform)\$(Configuration)\`

---

## IV. Client Project Configuration (MyApp)

### 4.1 Include Header File Path

Configure include directories in `MyApp.vcxproj`:

```101:101:MyApp/MyApp.vcxproj
      <AdditionalIncludeDirectories>$(ProjectDir)..\MyLibrary;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Properties
2. Configuration Properties → C/C++ → General
3. Additional Include Directories: Add `$(ProjectDir)..\MyLibrary`

**Explanation**:
- `$(ProjectDir)` is the project directory (`MyApp\`)
- `..\MyLibrary` is a relative path pointing to the `MyLibrary` directory
- This allows `main.cpp` to use `#include "MyLibrary.h"`

### 4.2 Set LIB File Path

Configure library directories in `MyApp.vcxproj`:

```106:106:MyApp/MyApp.vcxproj
      <AdditionalLibraryDirectories>$(SolutionDir)$(Platform)\$(Configuration);%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Properties
2. Configuration Properties → Linker → General
3. Additional Library Directories: Add `$(SolutionDir)$(Platform)\$(Configuration)`

**Explanation**:
- `$(SolutionDir)` is the solution directory (`DLL_Demo\`)
- `$(Platform)` is the platform (e.g., `x64`)
- `$(Configuration)` is the configuration (e.g., `Debug`)
- Full path: `DLL_Demo\x64\Debug\` (where `MyLibrary.lib` is located)

### 4.3 Link LIB File

Configure link dependencies in `MyApp.vcxproj`:

```107:107:MyApp/MyApp.vcxproj
      <AdditionalDependencies>MyLibrary.lib;%(AdditionalDependencies)</AdditionalDependencies>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Properties
2. Configuration Properties → Linker → Input
3. Additional Dependencies: Add `MyLibrary.lib`

**Explanation**:
- Only the filename `MyLibrary.lib` is needed, not the full path
- The linker will search for this file in "Additional Library Directories"

### 4.4 Add Project Reference (Recommended)

Add project reference in `MyApp.vcxproj`:

```173:175:MyApp/MyApp.vcxproj
    <ProjectReference Include="..\MyLibrary\MyLibrary.vcxproj">
      <Project>{A1B2C3D4-E5F6-4A5B-8C9D-0E1F2A3B4C5D}</Project>
    </ProjectReference>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Add → Reference
2. Select `MyLibrary` project
3. Click "OK"

**Advantages**:
- ✅ Automatically manages build order (build DLL first, then application)
- ✅ Automatically handles path configuration
- ✅ Easy to maintain and deploy

---

## V. DLL File Path Settings (Runtime)

### 5.1 DLL File Search Order

Windows searches for DLLs in the following order at runtime:

1. **Application directory** (most common)
   - `x64\Debug\MyApp.exe` and `MyLibrary.dll` are in the same directory

2. **System directories**
   - `C:\Windows\System32\` (64-bit programs)
   - `C:\Windows\SysWOW64\` (32-bit programs)

3. **Directories in PATH environment variable**
   - System PATH
   - User PATH

4. **Current working directory**

### 5.2 Recommended Solution: Output to Same Directory

**Method 1: Modify DLL output directory**

In `MyLibrary.vcxproj`:
```xml
<OutDir>$(SolutionDir)$(Platform)\$(Configuration)\</OutDir>
```

In `MyApp.vcxproj`:
```xml
<OutDir>$(SolutionDir)$(Platform)\$(Configuration)\</OutDir>
```

This way both DLL and EXE will be output to the `x64\Debug\` directory.

**Method 2: Copy DLL to application directory**

Add post-build event in `MyApp.vcxproj`:

```xml
<Target Name="PostBuild" AfterTargets="PostBuildEvent">
  <Copy SourceFiles="$(SolutionDir)$(Platform)\$(Configuration)\MyLibrary.dll" 
        DestinationFiles="$(OutDir)MyLibrary.dll" 
        SkipUnchangedFiles="true" />
</Target>
```

**Setting in Visual Studio**:
1. Right-click `MyApp` project → Properties
2. Configuration Properties → Build Events → Post-Build Event
3. Command Line: Add copy command

### 5.3 DLL Path During Debugging

When debugging in Visual Studio, you can set the working directory:

1. Right-click `MyApp` project → Properties
2. Configuration Properties → Debugging
3. Working Directory: `$(OutDir)`

---

## VI. Practical Usage Examples

### 6.1 Export C-Style Functions

In `MyLibrary.h`:

```20:25:MyLibrary/MyLibrary.h
extern "C" {
    // Simple math function examples
    MYLIBRARY_API int Add(int a, int b);
    MYLIBRARY_API int Multiply(int a, int b);
    MYLIBRARY_API const char* GetVersion();
}
```

**Explanation**:
- `extern "C"` avoids C++ name mangling
- Convenient for calling from C code or other languages

### 6.2 Export C++ Class

In `MyLibrary.h`:

```28:44:MyLibrary/MyLibrary.h
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
```

**Explanation**:
- `MYLIBRARY_API` modifies the entire class
- All public member functions of the class will be exported

### 6.3 Export Singleton Function

In `MyLibrary.h`:

```47:47:MyLibrary/MyLibrary.h
MYLIBRARY_API Calculator& GetCalculatorInstance();
```

Usage in `MyApp/main.cpp`:

```44:44:MyApp/main.cpp
    Calculator& calc2 = GetCalculatorInstance();
```

**Explanation**:
- Similar to the `VerificationSystemInstance()` pattern
- Provides a global access point

---

## VII. Complete Configuration Steps Summary

### 7.1 DLL Project (MyLibrary) Configuration Checklist

- [x] **Project Type**: Dynamic Library (.dll)
- [x] **Preprocessor Definitions**: Add `MYLIBRARY_EXPORTS`
- [x] **Output Directory**: `$(SolutionDir)$(Platform)\$(Configuration)\`
- [x] **Header File**: Define export macro `MYLIBRARY_API`
- [x] **Implementation File**: Implement all exported functions and classes

### 7.2 Client Project (MyApp) Configuration Checklist

- [x] **Include Directories**: Add `$(ProjectDir)..\MyLibrary`
- [x] **Library Directories**: Add `$(SolutionDir)$(Platform)\$(Configuration)`
- [x] **Link Dependencies**: Add `MyLibrary.lib`
- [x] **Project Reference**: Add reference to `MyLibrary` project
- [x] **Header File Include**: `#include "MyLibrary.h"`

### 7.3 Runtime DLL Path Configuration

- [x] **Unified Output Directory**: DLL and EXE output to the same directory
- [x] **Or Use Copy**: Post-build event copies DLL to EXE directory
- [x] **Or Set PATH**: Add DLL directory to PATH environment variable

---

## VIII. Common Issues and Troubleshooting

### 8.1 Link Error: Unresolved External Symbol

**Error Message**:
```
error LNK2019: unresolved external symbol "int __cdecl Add(int,int)" (?Add@@YAHHH@Z)
```

**Possible Causes**:
1. `MyLibrary.lib` is not linked
2. LIB file path is incorrect
3. Function signature mismatch

**Solutions**:
1. Check if `MyLibrary.lib` is in "Additional Dependencies"
2. Check if "Additional Library Directories" path is correct
3. Verify that function signatures in header and implementation files match

### 8.2 Runtime Error: DLL Not Found

**Error Message**:
```
System Error: The program can't start because MyLibrary.dll is missing from your computer
```

**Possible Causes**:
1. DLL file is not in the application directory
2. DLL file is not in PATH
3. Other DLLs that the DLL depends on are missing

**Solutions**:
1. Copy `MyLibrary.dll` to the directory where `MyApp.exe` is located
2. Use `Dependency Walker` to check DLL dependencies
3. Ensure all dependent DLLs are in accessible paths

### 8.3 Compilation Error: Undefined Identifier

**Error Message**:
```
error C2065: "MYLIBRARY_API": undeclared identifier
```

**Possible Causes**:
1. `MyLibrary.h` is not included
2. Include directory configuration is incorrect

**Solutions**:
1. Check if `#include "MyLibrary.h"` is correct
2. Check "Additional Include Directories" configuration

---

## IX. Comparison with VerificationTestSystem

| Feature | VerificationTestSystem | DLL_Demo |
|------|----------------------|----------|
| **Export Macro** | `INTEROPVERIFICATIONSYSTEM_API` | `MYLIBRARY_API` |
| **Macro Condition** | `VSINTEROP_EXPORTS` | `MYLIBRARY_EXPORTS` |
| **DLL Project** | `InteropToVerificationSystem` | `MyLibrary` |
| **Client Project** | `ApolloVerificationSystem` | `MyApp` |
| **Singleton Function** | `VerificationSystemInstance()` | `GetCalculatorInstance()` |
| **Purpose** | C++/CLI interop layer | Pure C++ DLL example |

---

## X. Debugging Tips

### 10.1 View DLL Exported Symbols

Use the `dumpbin` tool (included with Visual Studio):

```bash
# Open "Developer Command Prompt for VS"
cd DLL_Demo\x64\Debug
dumpbin /EXPORTS MyLibrary.dll
```

**Output Example**:
```
ordinal hint RVA      name
      1    0 00001000 Add
      2    1 00001010 Multiply
      3    2 00001020 GetVersion
      4    3 00001030 ??0Calculator@@QEAA@XZ
      5    4 00001040 ??1Calculator@@QEAA@XZ
      ...
```

### 10.2 Check DLL Dependencies

Use `dumpbin` to view DLL dependencies:

```bash
dumpbin /DEPENDENTS MyLibrary.dll
```

### 10.3 Debug DLL in Visual Studio

1. Set `MyApp` as the startup project
2. Set breakpoints in DLL code
3. Press F5 to start debugging
4. Visual Studio will automatically load DLL symbols

---

## XI. Best Practices

### 11.1 Naming Conventions

- **Export Macro**: `<ProjectName>_API` (e.g., `MYLIBRARY_API`)
- **Macro Condition**: `<ProjectName>_EXPORTS` (e.g., `MYLIBRARY_EXPORTS`)
- **Consistency**: Use unified naming conventions throughout the project

### 11.2 Header File Organization

- **Single header file**: Use conditional compilation, same header file works for both DLL and client
- **Clear comments**: Indicate which symbols are exported
- **Version information**: Provide version query function (e.g., `GetVersion()`)

### 11.3 Path Management

- **Use macros**: `$(SolutionDir)`, `$(Platform)`, `$(Configuration)`
- **Relative paths**: Avoid hardcoded absolute paths
- **Unified output**: DLL and EXE output to the same directory for easy deployment

### 11.4 Project References

- **Prefer project references**: Instead of manually configuring paths
- **Automatic build order**: Ensures DLL is built before the application
- **Easy maintenance**: Automatically updates when paths change

---

## XII. Summary

### 12.1 Key Points

1. **Export macro pattern**: Use conditional compilation to automatically switch between `dllexport`/`dllimport`
2. **Project configuration**: DLL project defines export macro, client project does not
3. **Path settings**:
   - **Include directories**: Find header files
   - **Library directories**: Find LIB files
   - **Link dependencies**: Link LIB files
   - **Runtime paths**: Find DLL files
4. **Project references**: Recommended to use project references for automatic dependency management

### 12.2 Configuration Checklist

**DLL Project**:
- [ ] Project Type: Dynamic Library
- [ ] Preprocessor Definitions: `MYLIBRARY_EXPORTS`
- [ ] Header File: Define `MYLIBRARY_API` macro

**Client Project**:
- [ ] Include Directories: Point to DLL header file directory
- [ ] Library Directories: Point to LIB file directory
- [ ] Link Dependencies: `MyLibrary.lib`
- [ ] Project Reference: Reference DLL project
- [ ] Runtime Path: DLL file is accessible

---

## XIII. Reference Resources

- [Microsoft Docs: Exporting from a DLL](https://docs.microsoft.com/en-us/cpp/build/exporting-from-a-dll)
- [Microsoft Docs: Importing into an Application](https://docs.microsoft.com/en-us/cpp/build/importing-into-an-application)
- [Microsoft Docs: dllexport, dllimport](https://docs.microsoft.com/en-us/cpp/cpp/dllexport-dllimport)
- [Visual Studio Project Property Pages Reference](https://docs.microsoft.com/en-us/cpp/build/reference/project-property-pages-reference)

---

**Document Version**: 1.0  
**Last Updated**: 2025-12-15  
**Based on Project**: DLL_Demo

