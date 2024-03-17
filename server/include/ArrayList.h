#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    size_t* array; // array of pointers to some object
    size_t length;
    size_t capacity;
} ArrayList;

ArrayList* ArrayList_create();
void ArrayList_push(ArrayList* list, size_t address);
size_t ArrayList_pop(ArrayList* list);
size_t ArrayList_indexOf(ArrayList* list, size_t address);
void ArrayList_removeIndex(ArrayList* list, size_t index);
void ArrayList_remove(ArrayList* list, size_t address);
void ArrayList_swap(ArrayList* list, size_t index1, size_t index2);
void ArrayList_destroy(ArrayList* list);

#endif /* ARRAYLIST_H */
