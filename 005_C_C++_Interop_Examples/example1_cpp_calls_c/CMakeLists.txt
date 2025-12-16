cmake_minimum_required(VERSION 3.10)
project(Example1_CPP_Calls_C LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# C library (math_utils)
add_library(math_utils STATIC
    c_lib/math.c
)

# Set include directories for the library
target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# C++ executable
add_executable(example1
    main.cpp
)

# Link the C library to the C++ executable
target_link_libraries(example1
    PRIVATE
        math_utils
)

# Set include directories for the executable
target_include_directories(example1
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Print configuration info
message(STATUS "Example 1: C++ Calling C Functions")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")

