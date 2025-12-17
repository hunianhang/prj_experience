// Complete usage examples of const in C++
// This is a complete, runnable example program demonstrating all usages of const
// Contains 16 complete examples:
// 1. Modifying variables - basic usage
// 2. Modifying pointers - three types (pointer to const, const pointer, const pointer to const)
// 3. Modifying references
// 4. Modifying function parameters
// 5. Modifying function return values
// 6. Modifying member variables
// 7. Modifying member functions
// 8. const objects
// 9. Top-level const and low-level const
// 10. const and mutable
// 11. const in templates
// 12. const and auto
// 13. const and STL containers
// 14. const and smart pointers
// 15. constexpr
// 16. const and function overloading

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ============================================================================
// 1. Modifying Variables - Basic Usage
// ============================================================================
void example1_basic_variable()
{
    std::cout << "\n=== 1. Modifying Variables - Basic Usage ===\n";
    
    const int x = 10;        // Constant, cannot be modified
    // x = 20;               // Error: cannot modify constant
    std::cout << "const int x = " << x << "\n";
    
    const double PI = 3.14159;
    std::cout << "const double PI = " << PI << "\n";
    
    const std::string name = "C++";
    std::cout << "const std::string name = " << name << "\n";
    
    // const variables must be initialized
    // const int y;          // Error: const variable must be initialized
    
    // const variables can be initialized with non-const values
    int normal = 100;
    const int const_from_normal = normal;  // Correct
    std::cout << "const int from normal variable = " << const_from_normal << "\n";
}

// ============================================================================
// 2. Modifying Pointers - Three Types
// ============================================================================
void example2_pointers()
{
    std::cout << "\n=== 2. Modifying Pointers - Three Types ===\n";
    
    int value = 10;
    int another = 20;
    
    std::cout << "Initial values: value = " << value << ", another = " << another << "\n";
    
    // 2.1 Pointer to const
    // const before * means the pointed-to value is immutable, but the pointer itself can change
    const int* ptr1 = &value;    // Pointer to const
    std::cout << "const int* ptr1 = &value, *ptr1 = " << *ptr1 << "\n";
    // *ptr1 = 30;               // Error: cannot modify value through ptr1
    ptr1 = &another;              // Correct: pointer itself can change
    std::cout << "ptr1 = &another, *ptr1 = " << *ptr1 << "\n";
    
    int const* ptr2 = &value;    // Equivalent to const int* ptr2
    std::cout << "int const* ptr2 (equivalent to const int*) = " << *ptr2 << "\n";
    
    // 2.2 Const pointer
    // const after * means the pointer itself is immutable, but the pointed-to value can change
    int* const ptr3 = &value;    // Const pointer
    *ptr3 = 30;                  // Correct: can modify pointed-to value
    std::cout << "int* const ptr3, *ptr3 = " << *ptr3 << ", value = " << value << "\n";
    // ptr3 = &another;          // Error: pointer itself cannot change
    
    // 2.3 Const pointer to const
    const int* const ptr4 = &value;  // Both pointer and pointed-to value are immutable
    std::cout << "const int* const ptr4 = " << *ptr4 << "\n";
    // *ptr4 = 30;              // Error
    // ptr4 = &another;         // Error
    
    // Memory tip: const before * means pointed-to value is immutable; const after * means pointer itself is immutable
}

// ============================================================================
// 3. Modifying References
// ============================================================================
void example3_references()
{
    std::cout << "\n=== 3. Modifying References ===\n";
    
    int value = 10;
    std::cout << "Initial value: value = " << value << "\n";
    
    // Reference to const
    const int& ref1 = value;     // Cannot modify value through ref1
    std::cout << "const int& ref1 = value, ref1 = " << ref1 << "\n";
    // ref1 = 20;                // Error: cannot modify
    
    // Note: There's no such thing as "const reference"
    // Because references are not objects, just aliases
    // But we can use const to modify the reference type, meaning the object cannot be modified through this reference
    
    // const references can bind to temporary objects
    const int& ref2 = 42;        // Correct: can bind to literal
    std::cout << "const int& ref2 = 42, ref2 = " << ref2 << "\n";
    
    // Non-const references cannot bind to temporary objects
    // int& ref3 = 42;           // Error: cannot bind to literal
    
    // const references can bind to objects of different types (requires type conversion)
    double d = 3.14;
    const int& ref4 = d;         // Correct: creates temporary object
    std::cout << "const int& ref4 = d(3.14), ref4 = " << ref4 << "\n";
}

// ============================================================================
// 4. Modifying Function Parameters
// ============================================================================
void example4_function_parameters(const int x, const int* ptr, const int& ref)
{
    // x is a const parameter, cannot be modified inside the function
    // ptr is a pointer to const
    // ref is a const reference, avoids copying and cannot modify the original object
    std::cout << "  Parameters x = " << x << ", *ptr = " << *ptr << ", ref = " << ref << "\n";
    // x = 100;      // Error: cannot modify const parameter
    // *ptr = 200;   // Error: cannot modify through const pointer
    // ref = 300;    // Error: cannot modify through const reference
}

void example4_demo()
{
    std::cout << "\n=== 4. Modifying Function Parameters ===\n";
    
    int a = 10;
    int b = 20;
    int c = 30;
    
    std::cout << "Before function call: a = " << a << ", b = " << b << ", c = " << c << "\n";
    example4_function_parameters(a, &b, c);
    std::cout << "After function call: a = " << a << ", b = " << b << ", c = " << c << " (unchanged)\n";
    
    // Advantage of const reference parameters: avoid copying large objects
    std::string large_string = "This is a very long string...";
    // void func1(std::string s);        // Will copy
    // void func2(const std::string& s); // Won't copy, recommended
}

// ============================================================================
// 5. Modifying Function Return Values
// ============================================================================
const int* example5_return_const_pointer()
{
    static int value = 10;
    return &value;  // Returns pointer to const, caller cannot modify through pointer
}

const int& example5_return_const_reference()
{
    static int value = 10;
    return value;   // Returns const reference, caller cannot modify
}

int* example5_return_nonconst_pointer()
{
    static int value = 20;
    return &value;  // Returns non-const pointer, caller can modify
}

void example5_demo()
{
    std::cout << "\n=== 5. Modifying Function Return Values ===\n";
    
    const int* ptr1 = example5_return_const_pointer();
    std::cout << "const int* ptr1 = " << *ptr1 << "\n";
    // *ptr1 = 100;  // Error: cannot modify through const pointer
    
    const int& ref1 = example5_return_const_reference();
    std::cout << "const int& ref1 = " << ref1 << "\n";
    // ref1 = 200;   // Error: cannot modify const reference
    
    int* ptr2 = example5_return_nonconst_pointer();
    std::cout << "int* ptr2 = " << *ptr2 << "\n";
    *ptr2 = 300;    // Correct: can modify
    std::cout << "After modification *ptr2 = " << *ptr2 << "\n";
}

// ============================================================================
// 6. Modifying Member Variables
// ============================================================================
class Example6_ConstMember
{
private:
    const int const_member_;     // const member variable
    static const int static_const_member_ = 100;  // Static const member (can be initialized in-class)
    
    // Note: Non-static const members cannot be initialized in-class (before C++11)
    
public:
    // const member variables must be initialized in the constructor's initializer list
    Example6_ConstMember(int val) : const_member_(val) 
    {
        // const_member_ = val;  // Error: cannot assign in constructor body
    }
    
    int getConstMember() const { return const_member_; }
    static int getStaticConstMember() { return static_const_member_; }
};

// Definition of static const member (if address is needed outside class)
const int Example6_ConstMember::static_const_member_;

void example6_demo()
{
    std::cout << "\n=== 6. Modifying Member Variables ===\n";
    
    Example6_ConstMember obj(50);
    std::cout << "const_member_ = " << obj.getConstMember() << "\n";
    std::cout << "static_const_member_ = " << Example6_ConstMember::getStaticConstMember() << "\n";
    
    // Each object can have different const member values
    Example6_ConstMember obj2(60);
    std::cout << "obj2.const_member_ = " << obj2.getConstMember() << "\n";
}

// ============================================================================
// 7. Modifying Member Functions
// ============================================================================
class Example7_ConstMemberFunction
{
private:
    int value_;
    mutable int mutable_value_;  // mutable member, can be modified even in const member functions
    mutable int call_count_;     // Used to count function calls
    
public:
    Example7_ConstMemberFunction(int v) : value_(v), mutable_value_(0), call_count_(0) {}
    
    // const member function: cannot modify non-mutable member variables
    int getValue() const
    {
        // value_ = 10;          // Error: cannot modify non-mutable member
        mutable_value_ = 10;     // Correct: can modify mutable member
        call_count_++;           // Correct: can modify mutable member
        return value_;
    }
    
    // Non-const member function
    void setValue(int v)
    {
        value_ = v;
    }
    
    // const overloading: can provide both const and non-const versions
    const int* getPtr() const
    {
        std::cout << "     Calling const version getPtr()\n";
        return &value_;
    }
    
    int* getPtr()  // Non-const version
    {
        std::cout << "     Calling non-const version getPtr()\n";
        return &value_;
    }
    
    int getCallCount() const { return call_count_; }
};

void example7_demo()
{
    std::cout << "\n=== 7. Modifying Member Functions ===\n";
    
    Example7_ConstMemberFunction obj(100);
    std::cout << "Initial value: " << obj.getValue() << "\n";
    std::cout << "Call count: " << obj.getCallCount() << "\n";
    
    // const objects can only call const member functions
    const Example7_ConstMemberFunction const_obj(200);
    std::cout << "const object value: " << const_obj.getValue() << "\n";
    const int* ptr1 = const_obj.getPtr();  // Calling const version
    
    // Non-const objects can call all member functions
    int* ptr2 = obj.getPtr();  // Calling non-const version
    obj.setValue(300);
    std::cout << "Modified value: " << obj.getValue() << "\n";
}

// ============================================================================
// 8. const Objects
// ============================================================================
class Example8_Class
{
private:
    int data_;
    
public:
    Example8_Class(int d) : data_(d) {}
    
    int getData() const { return data_; }
    void setData(int d) { data_ = d; }
};

void example8_demo()
{
    std::cout << "\n=== 8. const Objects ===\n";
    
    // const objects can only call const member functions
    const Example8_Class const_obj(10);
    std::cout << "const object value: " << const_obj.getData() << "\n";
    // const_obj.setData(20);    // Error: cannot call non-const member function
    
    // Non-const objects can call all member functions
    Example8_Class non_const_obj(20);
    std::cout << "Non-const object value: " << non_const_obj.getData() << "\n";
    non_const_obj.setData(30);
    std::cout << "After modification: " << non_const_obj.getData() << "\n";
    
    // const objects must be initialized at definition (if constructor exists)
    // const Example8_Class obj;  // Error: no default constructor
}

// ============================================================================
// 9. Top-level const and Low-level const
// ============================================================================
void example9_top_level_vs_low_level()
{
    std::cout << "\n=== 9. Top-level const and Low-level const ===\n";
    
    int i = 0;
    
    // Top-level const: the object itself is constant
    const int ci = 42;           // Top-level const
    std::cout << "Top-level const: const int ci = " << ci << "\n";
    
    int* const p1 = &i;         // Top-level const (pointer itself is constant)
    std::cout << "Top-level const pointer: int* const p1, *p1 = " << *p1 << "\n";
    *p1 = 10;                    // Correct: can modify pointed-to value
    std::cout << "After modification *p1 = " << *p1 << "\n";
    
    // Low-level const: the pointed-to object is constant
    const int* p2 = &ci;         // Low-level const (points to const)
    std::cout << "Low-level const pointer: const int* p2, *p2 = " << *p2 << "\n";
    
    const int* const p3 = p2;   // Both top-level and low-level const
    std::cout << "Top+Low-level const: const int* const p3, *p3 = " << *p3 << "\n";
    
    // In copy operations, top-level const is ignored, but low-level const must match
    p2 = p3;                    // Correct: both have low-level const
    std::cout << "p2 = p3 succeeded (low-level const matches)\n";
    
    // int* p4 = p2;             // Error: p4 doesn't have low-level const
    // Correct approach:
    const int* p4 = p2;         // Correct: p4 also has low-level const
    std::cout << "const int* p4 = p2 succeeded\n";
    
    // Top-level const in function parameters is ignored
    // void func1(int x);
    // void func2(const int x);    // These two function signatures are the same (top-level const ignored)
    
    // But low-level const is not ignored
    // void func3(int* p);
    // void func4(const int* p);   // These two function signatures are different
}

// ============================================================================
// 10. const and mutable
// ============================================================================
class Example10_Mutable
{
private:
    int value_;
    mutable int call_count_;    // mutable: can be modified even in const member functions
    mutable bool cache_valid_;   // Cache validity flag
    mutable int cached_value_;   // Cached value
    
public:
    Example10_Mutable(int v) : value_(v), call_count_(0), cache_valid_(false), cached_value_(0) {}
    
    int getValue() const
    {
        call_count_++;           // Correct: mutable members can be modified in const functions
        return value_;
    }
    
    // Using mutable to implement caching
    int getExpensiveValue() const
    {
        if (!cache_valid_)
        {
            // Simulate expensive computation
            cached_value_ = value_ * 2;
            cache_valid_ = true;
            std::cout << "     Computing and caching value\n";
        }
        else
        {
            std::cout << "     Using cached value\n";
        }
        return cached_value_;
    }
    
    void invalidateCache()
    {
        cache_valid_ = false;
    }
    
    int getCallCount() const { return call_count_; }
};

void example10_demo()
{
    std::cout << "\n=== 10. const and mutable ===\n";
    
    const Example10_Mutable obj(50);
    std::cout << "Calling getValue() 3 times:\n";
    obj.getValue();
    obj.getValue();
    obj.getValue();
    std::cout << "Call count: " << obj.getCallCount() << "\n";
    
    std::cout << "\nUsing mutable to implement caching:\n";
    std::cout << "First call: " << obj.getExpensiveValue() << "\n";
    std::cout << "Second call: " << obj.getExpensiveValue() << "\n";
    
    // Note: mutable cannot be used for const objects themselves, only for member variables
}

// ============================================================================
// 11. const in Templates
// ============================================================================
template<typename T>
void example11_template(const T& param)  // Using const reference to avoid copying
{
    std::cout << "   Template function parameter: " << param << "\n";
}

template<typename T>
const T& example11_max(const T& a, const T& b)  // Returns const reference
{
    return (a > b) ? a : b;
}

void example11_demo()
{
    std::cout << "\n=== 11. const in Templates ===\n";
    
    int a = 10, b = 20;
    example11_template(a);
    example11_template(b);
    
    const int& max_val = example11_max(a, b);
    std::cout << "max(" << a << ", " << b << ") = " << max_val << "\n";
    
    std::string s1 = "Hello";
    std::string s2 = "World";
    const std::string& max_str = example11_max(s1, s2);
    std::cout << "max(\"" << s1 << "\", \"" << s2 << "\") = \"" << max_str << "\"\n";
}

// ============================================================================
// 12. const and auto
// ============================================================================
void example12_const_auto()
{
    std::cout << "\n=== 12. const and auto ===\n";
    
    const int x = 10;
    auto y = x;                 // y's type is int (top-level const is ignored)
    std::cout << "const int x = " << x << ", auto y = x, y = " << y << " (type: int)\n";
    y = 20;                     // Correct: y is not const
    
    const auto z = x;           // z's type is const int
    std::cout << "const auto z = x, z = " << z << " (type: const int)\n";
    // z = 30;                  // Error: z is const
    
    const int* p = &x;
    auto q = p;                 // q's type is const int* (low-level const is preserved)
    std::cout << "const int* p, auto q = p (type: const int*)\n";
    // *q = 40;                 // Error: q points to const
    
    // Using decltype to preserve top-level const
    decltype(x) w = x;          // w's type is const int
    std::cout << "decltype(x) w = x (type: const int)\n";
    
    // auto& preserves top-level const
    auto& ref = x;              // ref's type is const int&
    std::cout << "auto& ref = x (type: const int&)\n";
}

// ============================================================================
// 13. const and STL Containers
// ============================================================================
void example13_stl_containers()
{
    std::cout << "\n=== 13. const and STL Containers ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    const std::vector<int> const_vec = {10, 20, 30};
    
    // Iterator for const containers
    std::vector<int>::const_iterator it = const_vec.begin();
    std::cout << "First element of const container: " << *it << "\n";
    // *it = 100;                // Error: const_iterator cannot modify elements
    
    // Iterator for non-const containers
    std::vector<int>::iterator it2 = vec.begin();
    *it2 = 100;                  // Correct: can modify
    std::cout << "First element after modification: " << *it2 << "\n";
    
    // cbegin() and cend() return const_iterator
    auto cit = vec.cbegin();     // const_iterator
    // *cit = 200;               // Error: cannot modify
    std::cout << "Using cbegin(): " << *cit << "\n";
}

// ============================================================================
// 14. const and Smart Pointers
// ============================================================================
void example14_smart_pointers()
{
    std::cout << "\n=== 14. const and Smart Pointers ===\n";
    
    int value = 10;
    
    // const smart pointer (pointer itself is const)
    std::unique_ptr<int> const ptr1 = std::make_unique<int>(value);
    // ptr1 = std::make_unique<int>(20);  // Error: pointer itself is const
    *ptr1 = 20;                          // Correct: can modify pointed-to value
    std::cout << "*ptr1 = " << *ptr1 << "\n";
    
    // Smart pointer to const
    std::unique_ptr<const int> ptr2 = std::make_unique<const int>(30);
    // *ptr2 = 40;                        // Error: pointed-to value is const
    std::cout << "*ptr2 = " << *ptr2 << "\n";
    
    // const smart pointer to const object
    const std::unique_ptr<const int> ptr3 = std::make_unique<const int>(50);
    // ptr3 = ...;                         // Error: pointer itself is const
    // *ptr3 = 60;                         // Error: pointed-to value is const
    std::cout << "*ptr3 = " << *ptr3 << "\n";
}

// ============================================================================
// 15. constexpr (C++11) - Extension of const
// ============================================================================
constexpr int example15_constexpr_func(int x)  // constexpr function
{
    return x * 2;
}

void example15_demo()
{
    std::cout << "\n=== 15. constexpr (Extension of const) ===\n";
    
    // constexpr variable: compile-time constant
    constexpr int x = 10;
    constexpr int y = example15_constexpr_func(5);
    std::cout << "constexpr int x = " << x << "\n";
    std::cout << "constexpr int y = " << y << "\n";
    
    // constexpr can be used where compile-time constants are required
    int arr[x];                  // Correct: x is a compile-time constant
    std::cout << "Array size: " << sizeof(arr) / sizeof(arr[0]) << "\n";
}

// ============================================================================
// 16. const and Function Overloading
// ============================================================================
class Example16_Overload
{
private:
    int value_;
    
public:
    Example16_Overload(int v) : value_(v) {}
    
    // const and non-const member functions can be overloaded
    void print() const
    {
        std::cout << "     Calling const version print(), value = " << value_ << "\n";
    }
    
    void print()
    {
        std::cout << "     Calling non-const version print(), value = " << value_ << "\n";
    }
    
    // const in parameters can also be used for overloading
    void func(int x) { std::cout << "     func(int)\n"; }
    void func(const int x) { std::cout << "     func(const int) - won't be called (top-level const ignored)\n"; }
    
    void func(int* p) { std::cout << "     func(int*)\n"; }
    void func(const int* p) { std::cout << "     func(const int*) - will be called (low-level const not ignored)\n"; }
};

void example16_demo()
{
    std::cout << "\n=== 16. const and Function Overloading ===\n";
    
    Example16_Overload obj(100);
    const Example16_Overload const_obj(200);
    
    std::cout << "Non-const object:\n";
    obj.print();                // Calling non-const version
    
    std::cout << "const object:\n";
    const_obj.print();          // Calling const version
    
    int x = 10;
    const int* p = &x;
    obj.func(&x);               // Calling func(int*)
    obj.func(p);                // Calling func(const int*)
}

// ============================================================================
// Summary
// ============================================================================
/*
Complete Summary of const Usage:

1. Modifying variables: const int x = 10;
2. Modifying pointers:
   - const int* p;      // Pointer to const
   - int* const p;     // Const pointer
   - const int* const p; // Const pointer to const
3. Modifying references: const int& ref;
4. Modifying function parameters: avoid copying and modification
5. Modifying function return values: return const pointer/reference
6. Modifying member variables: must be initialized in initializer list
7. Modifying member functions: cannot modify non-mutable members
8. const objects: can only call const member functions
9. Top-level const vs Low-level const
10. mutable: allows modification in const member functions
11. const overloading: can provide both const and non-const versions
12. const and auto: auto ignores top-level const, preserves low-level const
13. const and STL containers: const_iterator, cbegin(), cend()
14. const and smart pointers: various combinations
15. constexpr: compile-time constants (C++11)
16. const and function overloading: top-level const ignored, low-level const not ignored

Memory Tips:
- const before *: pointed-to value is immutable
- const after *: pointer itself is immutable
- Top-level const: object itself is constant (auto ignores it)
- Low-level const: pointed-to object is constant (auto preserves it)
*/

int main()
{
    std::cout << "========================================\n";
    std::cout << "   Complete Usage Examples of const in C++\n";
    std::cout << "========================================\n";
    
    example1_basic_variable();
    example2_pointers();
    example3_references();
    example4_demo();
    example5_demo();
    example6_demo();
    example7_demo();
    example8_demo();
    example9_top_level_vs_low_level();
    example10_demo();
    example11_demo();
    example12_const_auto();
    example13_stl_containers();
    example14_smart_pointers();
    example15_demo();
    example16_demo();
    
    std::cout << "\n========================================\n";
    std::cout << "   All examples completed!\n";
    std::cout << "========================================\n";
    
    return 0;
}

