#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    int line = 123;
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, line++);
    // Remember, the chunk contaions a reference to the constant array
    writeChunk(&chunk, constant, line++);
    writeChunk(&chunk, OP_RETURN, line++);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
