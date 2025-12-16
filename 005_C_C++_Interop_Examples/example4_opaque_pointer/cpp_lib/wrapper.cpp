#include "wrapper.h"
#include <string>

// C++ class (hidden from C)
class StringProcessor
{
private:
    std::string m_data;
    
public:
    void setData(const char* data) {
        m_data = data;
    }
    
    const char* getData() const {
        return m_data.c_str();
    }
    
    int getLength() const {
        return static_cast<int>(m_data.length());
    }
};

// C interface wrapper
extern "C" {
    // Using opaque pointer
    void* string_processor_create()
    {
        return new StringProcessor();
    }
    
    void string_processor_destroy(void* handle)
    {
        if (handle != nullptr) {
            delete static_cast<StringProcessor*>(handle);
        }
    }
    
    void string_processor_set_data(void* handle, const char* data)
    {
        if (handle != nullptr) {
            static_cast<StringProcessor*>(handle)->setData(data);
        }
    }
    
    const char* string_processor_get_data(void* handle)
    {
        if (handle != nullptr) {
            return static_cast<StringProcessor*>(handle)->getData();
        }
        return nullptr;
    }
    
    int string_processor_get_length(void* handle)
    {
        if (handle != nullptr) {
            return static_cast<StringProcessor*>(handle)->getLength();
        }
        return -1;
    }
}

