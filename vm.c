#include <stdarg.h>
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


// Stack operations
void resetStack() {
    vm.stackTop = vm.stack;
}

static void runtimeError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    size_t instruction = vm.ip - vm.chunk->code - 1;
    int line = vm.chunk->lines[instruction];
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
}

void push(Value value) {
    *vm.stackTop++ = value;
}

Value pop() {
    return *(--vm.stackTop);
}

static Value peek(int distance) {
    return vm.stackTop[-1 - distance];
}

void freeVM() {
}
static InterpretResult run() {

// Macros are faster than functions
// invariant: vm.ip points to next instruction to interpret
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(valueType, op) \
    do { \
      if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
        runtimeError("Operands must be numbers."); \
        return INTERPRET_RUNTIME_ERROR; \
      } \
      double b = AS_NUMBER(pop()); \
      double a = AS_NUMBER(pop()); \
      push(valueType(a op b)); \
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
            case OP_ADD:      BINARY_OP(NUMBER_VAL, +); break;
            case OP_SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
            case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
            case OP_DIVIDE:   BINARY_OP(NUMBER_VAL, /); break;
            case OP_NEGATE:
                  if (!IS_NUMBER(peek(0))) {
                      runtimeError("Operand must be a number.");
                      return INTERPRET_RUNTIME_ERROR;
                  }
                  push(NUMBER_VAL(-AS_NUMBER(pop())));
                  break;
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
            case OP_NIL: push(NIL_VAL); break;
            case OP_TRUE: push(BOOL_VAL(true)); break;
            case OP_FALSE: push(BOOL_VAL(false)); break;
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    Chunk chunk;
    initChunk(&chunk);

    if (!compile(source, &chunk)) {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();

    freeChunk(&chunk);
    return result;
}
