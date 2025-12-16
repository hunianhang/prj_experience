#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

// C interface
void* calculator_create();
void calculator_destroy(void* handle);
int calculator_add(void* handle, int a, int b);
int calculator_multiply(void* handle, int a, int b);

#ifdef __cplusplus
}
#endif

#endif // CALCULATOR_H

