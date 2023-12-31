#ifndef clox_compiler_h 
#define clox_compiler_h

#include "vm.h"

bool compile(VM* vm, const char* source, Chunk* chunk);

#endif // !clox_compiler_h

