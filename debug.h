#ifndef clox_debug_h 
#define clox_debug_h

#include "common.h"
#include "chunk.h"

void disassemble_chunk(Chunk* chunk, const char* name);

size_t disassemble_instruction(Chunk* chunk, size_t offset);

#endif // !clox_debug_h

