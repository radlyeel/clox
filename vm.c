#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"
#include "value.h"
#include <stdio.h>

VM vm; 

void initVM() {
    resetStack();
}

void freeVM() {
}
/*
static InterpretResult run() {

// Macros are faster than functions
// invariant: vm.ip points to next instruction to interpret
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
      double b = pop(); \
      double a = pop(); \
      push(a op b); \
    } while (false)


    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        // dump stack first
        
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");

        disassembleInstruction(vm.chunk,
                (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        // get the opcode from the chunk and 'dispatch' it.
        switch (instruction = READ_BYTE()) {
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
            case OP_NEGATE:   push(-pop()); break;
            case OP_RETURN:
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            case OP_CONSTANT: 
                { // Braces are needed to allow local declarations 
                  // They can be eliminated by moving their declaration and
                  // initialization above switch.  This is only an issue 
                  // because Vim is lame about braces inside 'switch'es
                    Value constant = READ_CONSTANT();
                    push(constant);
                    break;
                }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}
*/
InterpretResult interpret(const char* source) {
  compile(source);
  return INTERPRET_OK;
}

// Stack operations
void resetStack() {
    vm.stackTop = vm.stack;
}

void push(Value value) {
    *vm.stackTop++ = value;
}

Value pop() {
    return *(--vm.stackTop);
}

