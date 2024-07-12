#ifndef clox_table_h
#define clox_table_h

#include "common.h"
#include "value.h"

/*
Hash function objectives:
  deterministic; must always give same result for same input.
  uniform; should "scatter" a 'typical' set of inputs over its range.
  fast;  duh.

See also “double hashing”, “cuckoo hashing”, “Robin Hood hashing”.
We use "linear probing".

FNV-1a: http://www.isthe.com/chongo/tech/comp/fnv/
*/

typedef struct {
    ObjString* key;
    Value value;
} Entry;

typedef struct {
    int count;
    int capacity;
    Entry* entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableGet(Table* table, ObjString* key, Value* value);
bool tableSet(Table* table, ObjString* key, Value value);
bool tableDelete(Table* table, ObjString* key);
void tableAddAll(Table* from, Table* to);
ObjString* tableFindString(Table* table, const char* chars,
                           int length, uint32_t hash);

#endif
