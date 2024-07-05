#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef enum {
    VAL_BOOL,
    VAL_NIL, 
    VAL_NUMBER,
} ValueType;

// Use a tagged union to represent different underlying types.
typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
    // This is a commonly-used name for a multipurpose field.
    } as;
} Value;

// Sec. 18.2

#define AS_BOOL(value)    ((value).as.boolean)
#define AS_NUMBER(value)  ((value).as.number)

#define BOOL_VAL(value)   ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL           ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})


// For Value arrays, like std::vector<Value>
typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
