#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

// C interface declarations
int cpp_add(int a, int b);
int cpp_multiply(int a, int b);

// Global object interface
void calculator_init();
void calculator_cleanup();
int calculator_add(int a, int b);

#ifdef __cplusplus
}
#endif

#endif // CALCULATOR_H

