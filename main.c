#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {

    Chunk chunk;
    initChunk(&chunk);

    // Some tests
    
    // Create an entry in the constant pool and add it to the chunk list 
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT);
    writeChunk(&chunk, constant);

    // Finish with a "return"
    writeChunk(&chunk, OP_RETURN);

    // Display the resulting list
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
