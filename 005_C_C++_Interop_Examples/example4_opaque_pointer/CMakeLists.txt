cmake_minimum_required(VERSION 3.10)
project(Example4_Opaque_Pointer LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# C++ library (wrapper)
add_library(wrapper STATIC
    cpp_lib/wrapper.cpp
)

target_include_directories(wrapper
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# C executable
add_executable(example4
    main.c
)

# Link the C++ library to the C executable
target_link_libraries(example4
    PRIVATE
        wrapper
)

target_include_directories(example4
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Print configuration info
message(STATUS "Example 4: Opaque Pointer Pattern")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")

