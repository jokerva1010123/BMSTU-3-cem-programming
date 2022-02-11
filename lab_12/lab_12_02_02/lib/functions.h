#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

ARR_DLL void fibonacci_arr(int *arr, int n);
ARR_DLL int make_new_arr(int *arr, int *new, int size, int set_size);

#endif // !_FUNCTIONS_H_
