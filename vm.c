#include <stdio.h>
#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm; 

static void resetStack() {
  vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {
}

void push(Value value) {
    //TODO  Change tp *vm.stackTop++ = value
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    //TODO  Change to return *(--vm.stackTop)
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run() {
    //This is looking a lot like Forth
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    // Note this trick to scope-control a macro See Sec. 15.3.1
#define BINARY_OP(op) \
    do { \
      double b = pop(); \
      double a = pop(); \
      push(a op b); \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
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
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                                  Value constant = READ_CONSTANT();
                                  push(constant);
                                  break;
                              }
            case OP_RETURN: {
                                printValue(pop());
                                printf("\n");
                                return INTERPRET_OK;
                            }
            case OP_NEGATE:   push(-pop()); break;
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;

        }
    }

#undef READ_CONSTANT
#undef READ_BYTE
#undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;

  vm.ip = vm.chunk->code;
  return run();
}

