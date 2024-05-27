#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// Enum of opcodes
typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;


typedef struct {
  uint8_t* code;
  // These two fields are needed for this to be a dynamic array, like the
  // STL std::vector<uint8_t> in C++
  int count;
  int capacity;
  // Each Chunk has its own constant array
  ValueArray constants;

} Chunk;

// Prototype of initialization function
void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
int  addConstant(Chunk* chunk, Value value);

#endif
