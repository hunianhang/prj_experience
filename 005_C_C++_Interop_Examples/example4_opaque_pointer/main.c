#include <stdio.h>
#include "cpp_lib/wrapper.h"

int main()
{
    printf("=== Example 4: Opaque Pointer Pattern ===\n");
    
    // Create C++ object
    StringProcessorHandle handle = string_processor_create();
    
    if (handle == NULL) {
        printf("Error: Failed to create string processor\n");
        return 1;
    }
    
    // Use C++ object through C interface
    string_processor_set_data(handle, "Hello, World!");
    
    const char* data = string_processor_get_data(handle);
    int length = string_processor_get_length(handle);
    
    printf("Data: %s\n", data);
    printf("Length: %d\n", length);
    
    // Test with different data
    string_processor_set_data(handle, "C and C++ Interoperability");
    data = string_processor_get_data(handle);
    length = string_processor_get_length(handle);
    
    printf("\nUpdated Data: %s\n", data);
    printf("Updated Length: %d\n", length);
    
    // Destroy C++ object
    string_processor_destroy(handle);
    
    printf("\nString processor destroyed successfully\n");
    
    return 0;
}

