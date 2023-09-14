#include "DLList.h"
#include <stdlib.h>
#include <stdio.h>


DLNode* DL_head(DLList* ls) {
    return ls->head;
}


void* DL_payload(DLNode* node) {
    return node->payload;
}
        
DLNode* DL_newnode(void* payload) {
    DLNode* node = (DLNode*) malloc(sizeof(DLNode));
    if (node) {
        node->payload = payload;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

// Accessors to hide details from user
void DL_reset_cursor(DLList* ls) {
    ls->cursor = ls->head;
}

// advance the cursor and return it;
DLNode* DL_next(DLList* ls) {
    ls->cursor = ls->cursor->next;
    return ls->cursor;
}

// Return the cursor but don't modify it
DLNode* DL_current(DLList* ls) {
    return ls->cursor;
}

// Reverse the cursor and return it
DLNode* DL_prev(DLList* ls) {
    ls->cursor = ls->cursor->prev;
    return ls->cursor;
}


// New nodes are inserted AFTER the cursor, and the cursor is updated to tyhe just-inserted node.
// This means that after a sequence of insertions the list is in insertion order
// Drawing a picture here would be helpful; absent that, envision three nodes lined up: left, center, right.  The new node is going between center and right.
// TODO Add ability to insert BEFORE the cursor
// TODO  Think about thread safety
// TODO This only works for inserting after the cursor
void DLList_insert(DLList* ls, DLNode* new_node) {
    if (ls->cursor) {
        // This may be a target for optimizing
        DLNode* center = ls->cursor;
        //DLNode* left = center->prev;
        DLNode* right = center->next;
        center->next = new_node;
        if (right) {
            right->prev = new_node;
        } else {
            // right is NULL; this node is now the tail
            ls->tail = new_node;
        }
        new_node->prev = center;
        new_node->next = right;
        ls->cursor = new_node;
    } else {
        // the first insert is easy
        ls->cursor = new_node;
        ls->head = new_node;
        ls->tail = new_node;
        // Leave new_node's prev and next at NULL
    }
}

DLList* DLList_new() {
    DLList* newls = (DLList *) calloc(1, sizeof(DLList));
    // calloc sets everything to 0, so nothing more needs to be done
    // fprintf(stderr, "From DLList_new(), returning %p\n", newls);

    return newls;
}

void dumpList(DLList* ls) {
    fprintf(stderr, "List: \n");
    fprintf(stderr, "  Head: %p \n", ls->head);
    fprintf(stderr, "  Tail: %p \n", ls->tail);
    fprintf(stderr, "  Cursor: %p \n", ls->cursor);
    fprintf(stderr, "\n");
    return;
}

void dumpNode(DLNode* node) {
    fprintf(stderr, "Node: %p\n", node);
    fprintf(stderr, "  Payload: %d\n",*(int*)node->payload);
    fprintf(stderr, "  prev: %p\n", node->prev);
    fprintf(stderr, "  next: %p\n", node->next);
    fprintf(stderr, "\n");
    return;
}
    
