#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 10

typedef struct {
    size_t* array; // array of pointers to some object
    size_t length;
    size_t capacity;
} ArrayList;

ArrayList* ArrayList_create()
{
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));

    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    list->array = (size_t*)malloc(INIT_CAPACITY * sizeof(size_t));

    if (list->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(list);
        exit(EXIT_FAILURE);
    }

    list->length = 0;
    list->capacity = INIT_CAPACITY;

    return list;
}

float _ArrayList_loadFactor(ArrayList* list)
{
    return (float)list->length / list->capacity;
}

float _ArrayList_resize(ArrayList* list, size_t newCapacity)
{
    list->array = (size_t*)realloc(list->array, newCapacity * sizeof(size_t));

    if (list->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    list->capacity = newCapacity;
    return _ArrayList_loadFactor(list);
}

void ArrayList_push(ArrayList* list, size_t address)
{
    if (_ArrayList_loadFactor(list) > 0.75) {
        _ArrayList_resize(list, list->capacity * 2);
    }

    list->array[list->length++] = address;
}

size_t ArrayList_pop(ArrayList* list)
{
    if (_ArrayList_loadFactor(list) < 0.25) {
        _ArrayList_resize(list, list->capacity / 2);
    }

    if (list->length > 0) {
        return list->array[--list->length];
    }
    return 0;
}

size_t ArrayList_indexOf(ArrayList* list, size_t address)
{
    for (int i = 0; i < list->length; ++i) {
        if (list->array[i] == address) {
            return i;
        }
    }
    return -1;
}

void ArrayList_removeIndex(ArrayList* list, size_t index)
{
    if (index >= list->length) return;

    for (int i = index; i < list->length - 1; ++i) {
        list->array[i] = list->array[i + 1];
    }
    list->length--;

    if (_ArrayList_loadFactor(list) < 0.25) {
        _ArrayList_resize(list, list->capacity / 2);
    }
}

void ArrayList_remove(ArrayList* list, size_t address)
{
    size_t index = ArrayList_indexOf(list, address);
    if (index != -1) {
        ArrayList_removeIndex(list, index);
    }

    if (_ArrayList_loadFactor(list) < 0.25) {
        _ArrayList_resize(list, list->capacity / 2);
    }
}

void ArrayList_swap(ArrayList* list, size_t index1, size_t index2)
{
    if (index1 >= list->length || index2 >= list->length) return;

    size_t temp = list->array[index1];
    list->array[index1] = list->array[index2];
    list->array[index2] = temp;
}

void ArrayList_destroy(ArrayList* list)
{
    free(list->array);
    free(list);
}

// =====================TEST=====================

// int main()
// {

//     size_t* array = (size_t*)malloc(1 * sizeof(size_t));
//     if (array == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     int a = 10;

//     array[0] = (size_t)&a;

//     int deref = *(int*)(array[0]);

//     // printf("First element: %zu\n", *(int*)(array[0]));
//     // printf("Casted to size_t: %zu\n", &a);
//     return 0;
// }