#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "object.h"

void * reallocate(void* pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, new_size);

  if (result == NULL) {
    fprintf(stderr, "clox: out of memory.");
  }

  return result;
}

void free_objects(Object *head) {
  Object* object = head;

  while (object != NULL) {
    Object* next = object->next;
    free_object(object);
    object = next;
  }
}

void free_object(Object* object) {
  switch (object->type) {
    case OBJ_STRING: {
      ObjectString* str = (ObjectString*) object;
      FREE_ARRAY(char, str->chars, str->length + 1);
      FREE(ObjectString, object);
    }
    case OBJ_FUNCTION: {
      ObjectFunction* function = (ObjectFunction*)object;
      Chunk_free(&function->chunk);
      FREE(ObjectFunction, object);
      break;
    }
    case OBJ_NATIVE_FN: {
      FREE(ObjectFunction, object);
      break;
    }
  }
}

