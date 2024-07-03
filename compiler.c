#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

typedef struct {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

Parser parser;

Chunk* compilingChunk;

static Chunk* currentChunk() {
    return compilingChunk;
}

// Format and display error
static void errorAt(Token* token, const char* message) {
    // Knock-on error message suppression (17.2.1)
    if (parser.panicMode) return;
    parser.panicMode = true;

    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
        // Nothing.
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }

    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}


// Report error to user
static void errorAtCurrent(const char* message) {
    errorAt(&parser.current, message);
}

static void error(const char* message) {
    errorAt(&parser.previous, message);
}

// advance through all error tokens to nexrt valid token
static void advance() {
    // LL(1)
    parser.previous = parser.current;

    // Process all error tokens until we get something useful
    for (;;) {
        parser.current = scanToken();
        if (parser.current.type != TOKEN_ERROR) break;
        errorAtCurrent(parser.current.start); 
    } 
}

static void consume(TokenType type, const char* message) {
    if (parser.current.type == type) {
        advance();
        return;
    }

    errorAtCurrent(message);
}

static void emitByte(uint8_t byte) {
    writeChunk(currentChunk(), byte, parser.previous.line);
}

// Useful for an opcode followed immediately by an operand
static void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

static void emitReturn() {
    emitByte(OP_RETURN);
}

static void endCompiler() {
    emitReturn();
}

// Map each token type to a different kind of expression.  Define a function
// for each expression that outputs the appropriate bytecode. Build an
// array of function pointers. The indexes in the array correspond to the
// TokenType enum values, and the function at each index is the code to compile
// an expression of that token type.

static uint8_t makeConstant(Value value) {
    int constant = addConstant(currentChunk(), value);
    // NB: This limits Lox to 256 constants per chunk.  Consider
    //      extending or removing this limit.
    if (constant > UINT8_MAX) {
        error("Too many constants in one chunk.");
        return 0;
    }

    return (uint8_t)constant;
}

static void emitConstant(Value value) {
    emitBytes(OP_CONSTANT, makeConstant(value));
}

// To compile number literals, store a pointer to the following function at
// the TOKEN_NUMBER index in the array.
static void number() {
    // strtod: https://cplusplus.com/reference/cstdlib/strtod/
    //    strtod is a good example of Rust's raison d'etre
    //    because an ill-formed string returns 0.
    double value = strtod(parser.previous.start, NULL);
    emitConstant(value);
}

// Note that grouping isn't visible in the bytecode stream
static void grouping() {
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

// Unary operators, such as negation
static void unary() {
    TokenType operatorType = parser.previous.type;

    // Compile the operand.
    expression();

    // Emit the operator instruction.
    switch (operatorType) {
        case TOKEN_MINUS: emitByte(OP_NEGATE); break;
        default: return; // Unreachable; satisfies compiler.
    }
}

static void parsePrecedence(Precedence precedence) {
  // What goes here?
}

bool compile(const char* source, Chunk* chunk) {
    initScanner(source);
    compilingChunk = chunk;

    // Clear panic mode
    parser.hadError = false;
    parser.panicMode = false;

    advance();
    expression();
    consume(TOKEN_EOF, "Expected end of expression.");

    endCompiler();

    return !parser.hadError;
}
