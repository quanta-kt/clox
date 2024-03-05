#ifndef clox_compiler_h 
#define clox_compiler_h

#include "vm.h"

ObjectFunction* compile(VM* vm, const char* source);

#endif // !clox_compiler_h

