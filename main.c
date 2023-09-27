#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {

    initVM();
    
    Chunk chunk;
    initChunk(&chunk);

    // Some tests
    
    // Create an entry in the constant pool and add it to the chunk list 
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_RETURN, 123);

    // Display the resulting list
    //disassembleChunk(&chunk, "test chunk");

    // Interpret the chunk
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}
