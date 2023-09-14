#include <stdio.h>
#include <stdlib.h>
#include "DLList.h"

// to keep things simple, test with integer payloads
typedef int Payload_t;

void* new_node(Payload_t data) {
    DLNode* node =  NULL;

    // Allocate space to store payload data and store the data there
    void* payload = malloc(sizeof(Payload_t));
    if (payload) {
        *(Payload_t*)payload = data;

        // Get a fresh node and load our data into the payload
        node = DL_newnode(payload);
    }
   
    return  (void*) node;
}

void show_list(DLList* ls) {
    DL_reset_cursor(ls);
    DLNode* current = DL_current(ls);
    while (current) {
        int* datum = (int*)DL_payload(current);
        printf("%d ", *datum);
        current = DL_next(ls);
    }
    printf("\n");
}

        
        
int main(int argc, char* args[]) {
    DLList* ls = DLList_new();
    DLList_insert(ls, new_node(1));
    DLList_insert(ls, new_node(2));
    DLList_insert(ls, new_node(3));
    show_list(ls);
}
