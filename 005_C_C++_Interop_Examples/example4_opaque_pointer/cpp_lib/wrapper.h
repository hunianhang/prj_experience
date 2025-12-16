#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// Opaque pointer type
typedef void* StringProcessorHandle;

// C interface
StringProcessorHandle string_processor_create();
void string_processor_destroy(StringProcessorHandle handle);
void string_processor_set_data(StringProcessorHandle handle, const char* data);
const char* string_processor_get_data(StringProcessorHandle handle);
int string_processor_get_length(StringProcessorHandle handle);

#ifdef __cplusplus
}
#endif

#endif // WRAPPER_H

