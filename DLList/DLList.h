#ifndef DLLIST_H
#define DLLIST_H

typedef struct _DLNode {
    void*  payload;    // List processing doesn't care about the payload
    struct _DLNode * prev;
    struct _DLNode * next;
} DLNode;

DLNode* DL_newnode(void* pl);

typedef struct {
    // The cursor, if not NULL, points ate the "currently active" node
    DLNode* cursor;
    DLNode* head;
    DLNode* tail;
} DLList;

void DL_reset_cursor(DLList* ls);

// Accessors to hide details from user
DLNode* DL_head(DLList* ls);
// advance the cursor and return it;
DLNode* DL_next(DLList* ls);
// Return the cursor but don't modify it
DLNode* DL_current(DLList* ls);
// Reverse the cursor and return it
DLNode* DL_prev(DLList* ls);
// Get the current node's payload pointer
void* DL_payload(DLNode* node);
// New nodes are inserted AFTER the cursor, and the cursor is updated to tyhe just-inserted node.
// This means that after a sequence of insertions the list is in insertion order
void DLList_insert(DLList* ls, DLNode* new_node);
DLList* DLList_new();

// Debugging
void dumpList(DLList* ls);
void dumpNode(DLNode* node);
#endif // DLLIST_H
