#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)
#define IS_STRING(value)       isObjType(value, OBJ_STRING)

#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)


typedef enum {
    OBJ_STRING,
} ObjType;

//TODO grok the discussion of this; search "6.7.2.1 13", C reference.
// Summary: 'Given an ObjString*, you can safely cast it to Obj* and then 
// access the type field from it.'
struct Obj {
    ObjType type;
    struct Obj* next;     //useful for GC
};

struct ObjString {
    Obj obj;
    int length;
    char* chars;
};

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
