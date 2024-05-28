#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

#ifdef DEBUG_TRACE_EXECUTION
#include <stdio.h>
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dprintf(...)
#endif

// Entire chunk
void disassembleChunk(Chunk* chunk, const char* name);
// One instruction (at 'offset' in chunk
int disassembleInstruction(Chunk* chunk, int offset);

#endif
