#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"
#include "table.h"
#define STACK_MAX 256

// The one global VM
//TODO:  Eliminate tho "global-ness" so we can integrate th interpreter into
// an app. Seee footnote in 15.1
typedef struct {
  Chunk* chunk;
  uint8_t* ip;
  // Value Stack
  Value stack[STACK_MAX];
  // pointer to next available slot
  Value* stackTop;
  Table strings;
  Obj*   objects;    // For GC
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void resetStack();
void push(Value value);
Value pop();



#endif


