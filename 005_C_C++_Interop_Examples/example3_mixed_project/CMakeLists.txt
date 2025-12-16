cmake_minimum_required(VERSION 3.10)
project(Example3_Mixed_Project LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# C library (math_utils)
add_library(math_utils STATIC
    c_code/math_utils.c
)

target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# C++ library (calculator)
add_library(calculator STATIC
    cpp_code/calculator.cpp
)

target_include_directories(calculator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# C++ main program
add_executable(example3
    main.cpp
)

# Link both libraries to the main program
target_link_libraries(example3
    PRIVATE
        math_utils
        calculator
)

target_include_directories(example3
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Print configuration info
message(STATUS "Example 3: Mixed C/C++ Project")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")

