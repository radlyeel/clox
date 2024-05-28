#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"
int main(int argc, const char* argv[]) {
    initVM();

    Chunk chunk;
    initChunk(&chunk);
    int line = 123;
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, line++);
    // Remember, the chunk contains a reference to the constant array
    writeChunk(&chunk, constant, line++);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIVIDE, 123);

    writeChunk(&chunk, OP_NEGATE, line++);
    writeChunk(&chunk, OP_RETURN, line++);
    dprintf("Ready to disasssemble\n");
    disassembleChunk(&chunk, "test chunk");
    dprintf("Ready to interpret\n");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}
