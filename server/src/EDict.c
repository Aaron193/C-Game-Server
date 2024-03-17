#include "../include/ArrayList.h"
#include "../include/HashMap.h"

typedef struct {
    ArrayList* list;
    HashMap* map;
} EDict;

EDict* EDict_create()
{
    EDict* dict = (EDict*)malloc(sizeof(EDict));
    if (dict == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dict->list = ArrayList_create();
    dict->map = HashMap_create();

    return dict;
}

void EDict_insert(EDict* dict, size_t id, size_t address)
{
    ArrayList_push(dict->list, address);
    HashMap_set(dict->map, id, dict->list->length - 1);
}

size_t EDict_find(EDict* dict, size_t id)
{
    size_t index = HashMap_get(dict->map, id);
    if (index == (size_t)-1) return NULL; // cast for compiler

    return dict->list->array[index];
}

void EDict_remove(EDict* dict, size_t id)
{
    size_t index = HashMap_get(dict->map, id);
    if (index == (size_t)-1) return; // cast for compiler

    size_t len = dict->list->length;

    ArrayList_swap(dict->list, index, len - 1);
    ArrayList_pop(dict->list);

    HashMap_remove(dict->map, id);
}

void EDict_destroy(EDict* dict)
{
    ArrayList_destroy(dict->list);
    HashMap_destroy(dict->map);
    free(dict);
}