# DLL Creation and Usage Demo Project

This demo project demonstrates how to create and use DLLs (Dynamic Link Libraries) on Windows.

## Project Structure

```
DLL_Demo/
├── MyLibrary/              # DLL project
│   ├── MyLibrary.h         # Export header file (contains export macro definition)
│   ├── MyLibrary.cpp       # DLL implementation file
│   └── MyLibrary.vcxproj   # Visual Studio project file
├── MyApp/                  # Console application project using the DLL
│   ├── main.cpp            # Main program demonstrating DLL usage
│   └── MyApp.vcxproj       # Visual Studio project file
├── DLL_Demo.sln            # Visual Studio solution file
└── README.md               # This file
```

## Core Concept: `MYLIBRARY_API` Macro

### Definition in `MyLibrary.h`:

```cpp
#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)   // When compiling DLL: export symbols
#else
#define MYLIBRARY_API __declspec(dllimport)   // When using DLL: import symbols
#endif
```

### How It Works:

1. **When compiling the DLL project**:
   - The `MYLIBRARY_EXPORTS` preprocessor macro is defined in project settings
   - `MYLIBRARY_API` expands to `__declspec(dllexport)`
   - Marks functions and classes to be exported for use by other modules

2. **In projects using the DLL**:
   - `MYLIBRARY_EXPORTS` is not defined
   - `MYLIBRARY_API` expands to `__declspec(dllimport)`
   - Tells the linker that these symbols need to be imported from the DLL

3. **Advantages**:
   - The same header file can be reused in both the DLL and the consuming project
   - Automatically switches between export/import based on compilation context
   - This is the standard pattern for Windows DLL development

## Project Configuration Details

### MyLibrary Project (DLL):

1. **Project Type**: `ConfigurationType = DynamicLibrary`
2. **Preprocessor Definitions**: Add `MYLIBRARY_EXPORTS`
   - Already configured in `MyLibrary.vcxproj`:
   ```xml
   <PreprocessorDefinitions>MYLIBRARY_EXPORTS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
   ```
3. **Output Files**:
   - `MyLibrary.dll` - Dynamic link library
   - `MyLibrary.lib` - Import library (used during linking)

### MyApp Project (Using DLL):

1. **Project Type**: `ConfigurationType = Application`
2. **Include Directories**: Add `MyLibrary` directory to find `MyLibrary.h`
3. **Library Directories**: Add DLL output directory to find `MyLibrary.lib`
4. **Link Libraries**: Add `MyLibrary.lib` to link dependencies
5. **Project References**: Add reference to `MyLibrary` project (ensures build order)

## Build Steps

### Method 1: Using Visual Studio

1. Open `DLL_Demo.sln`
2. Select configuration (Debug/Release) and platform (x86/x64)
3. Right-click solution → "Build Solution"
4. Build order:
   - First build `MyLibrary` (generates DLL and LIB)
   - Then build `MyApp` (links to DLL)

### Method 2: Using Command Line

```bash
# Navigate to project directory
cd DLL_Demo

# Build using MSBuild (requires Visual Studio Developer Command Prompt)
msbuild DLL_Demo.sln /p:Configuration=Debug /p:Platform=x64
```

## Running the Program

After building, the executable is located at:
- `x64\Debug\MyApp.exe` (Debug x64)
- `Win32\Debug\MyApp.exe` (Debug Win32)

**Note**: At runtime, ensure `MyLibrary.dll` is in one of the following locations:
1. Same directory as `MyApp.exe`
2. A directory in the system PATH environment variable
3. Windows system directory

## Demo Content

The `MyApp` program demonstrates three ways to use a DLL:

1. **C-style functions**:
   - `Add()`, `Multiply()`, `GetVersion()`

2. **C++ class (direct instantiation)**:
   - Usage of `Calculator` class

3. **Singleton pattern** (similar to `VerificationSystemInstance`):
   - `GetCalculatorInstance()` function

## Comparison with VerificationTestSystem

| Feature | VerificationTestSystem | This Demo Project |
|---------|----------------------|-------------------|
| DLL export macro | `INTEROPVERIFICATIONSYSTEM_API` | `MYLIBRARY_API` |
| Export macro condition | `VSINTEROP_EXPORTS` | `MYLIBRARY_EXPORTS` |
| Singleton function | `VerificationSystemInstance()` | `GetCalculatorInstance()` |
| DLL project | `InteropToVerificationSystem` | `MyLibrary` |
| Project using DLL | `ApolloVerificationSystem` | `MyApp` |

## Frequently Asked Questions

### Q: Why do we need the `.lib` file?
A: The `.lib` file is an import library containing stub information about exported symbols in the DLL. The linker uses it to resolve symbols, but at runtime, the actual code is called from the DLL.

### Q: How to debug a DLL?
A: In Visual Studio:
1. Set `MyApp` as the startup project
2. Set breakpoints in DLL code
3. Press F5 to start debugging
4. Visual Studio will automatically load DLL symbols

### Q: How to view exported symbols from a DLL?
A: Use Visual Studio's `dumpbin` tool:
```bash
dumpbin /EXPORTS MyLibrary.dll
```

Or use the `Dependency Walker` tool.

## Further Reading

- [Microsoft Docs: Exporting from a DLL](https://docs.microsoft.com/en-us/cpp/build/exporting-from-a-dll)
- [Microsoft Docs: Importing into an Application](https://docs.microsoft.com/en-us/cpp/build/importing-into-an-application)
