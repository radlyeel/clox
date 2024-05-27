#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

// Entire chunk
void disassembleChunk(Chunk* chunk, const char* name);
// One instruction (at 'offset' in chunk
int disassembleInstruction(Chunk* chunk, int offset);

#endif
