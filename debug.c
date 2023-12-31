#include <stdio.h>

#include "chunk.h"
#include "debug.h"

static size_t constant_instruction(const char* name, const Chunk* chunk, const size_t offset);
static size_t constant_long_instruction(const char* name, const Chunk* chunk, const size_t offset);
static size_t simple_instruction(const char* name, int offset);

void disassemble_chunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (size_t offset = 0; offset < chunk->count;) {
    offset = disassemble_instruction(chunk, offset);
  }
}

size_t disassemble_instruction(Chunk* chunk, size_t offset) {
  printf("%04zu ", offset);

  size_t line = Chunk_get_line(chunk, offset);

  if (offset > 0 && line == Chunk_get_line(chunk, offset - 1)) {
    printf("   | ");
  } else {
    printf("%4zu ", line);
  }

  uint8_t instruction = chunk->code[offset];

  switch (instruction) {  
    case OP_LOAD_CONST:
      return constant_instruction("OP_LOAD_CONST", chunk, offset);
    case OP_LOAD_CONST_LONG:
      return constant_long_instruction("OP_LOAD_CONST_LONG", chunk, offset);
    case OP_DEF_GLOBAL:
      return constant_instruction("OP_DEF_GLOBAL", chunk, offset);
    case OP_DEF_GLOBAL_LONG:
      return constant_long_instruction("OP_DEF_GLOBAL_LONG", chunk, offset);
    case OP_GET_GLOBAL:
      return constant_instruction("OP_GET_GLOBAL", chunk, offset);
    case OP_GET_GLOBAL_LONG:
      return constant_long_instruction("OP_GET_GLOBAL_LONG", chunk, offset);
    case OP_SET_GLOBAL:
      return constant_instruction("OP_SET_GLOBAL", chunk, offset);
    case OP_SET_GLOBAL_LONG:
      return constant_long_instruction("OP_SET_GLOBAL_LONG", chunk, offset);

    case OP_NIL:
      return simple_instruction("OP_NIL", offset);
    case OP_FALSE:
      return simple_instruction("OP_FALSE", offset);
    case OP_TRUE:
      return simple_instruction("OP_TRUE", offset);
    case OP_NEGATE:
      return simple_instruction("OP_NEGATE", offset);
    case OP_ADD:
      return simple_instruction("OP_ADD", offset);
    case OP_SUB:
      return simple_instruction("OP_SUB", offset);
    case OP_DIV:
      return simple_instruction("OP_DIV", offset);
    case OP_MUL:
      return simple_instruction("OP_MUL", offset);
    case OP_RETURN:
      return simple_instruction("OP_RETURN", offset);
    case OP_NOT:
      return simple_instruction("OP_NOT", offset);
    case OP_EQUAL:
      return simple_instruction("OP_EQUAL", offset);
    case OP_GREATER:
      return simple_instruction("OP_GREATER", offset);
    case OP_LESS:
      return simple_instruction("OP_LESS", offset);
    case OP_PRINT:
      return simple_instruction("OP_PRINT", offset);
    case OP_POP:
      return simple_instruction("OP_POP", offset);

    default:
      printf("Unknown opcode: %d\n", instruction);
      return offset + 1;
  }
}

static size_t simple_instruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static size_t constant_instruction(const char* name, const Chunk* chunk, const size_t offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  Value_print(chunk->constants.values[constant]);
  printf("'\n");

  return offset + 2;
}

static size_t constant_long_instruction(const char* name, const Chunk* chunk, const size_t offset) {
  const uint8_t a = chunk->code[offset + 1];
  const uint8_t b = chunk->code[offset + 2];
  const uint8_t c = chunk->code[offset + 3];

  const uint32_t constant = a | (b << 8) | (c << 8);

  printf("%-16s %4u '", name, constant);
  Value_print(chunk->constants.values[constant]);
  printf("'\n");

  return offset + 4;
}

