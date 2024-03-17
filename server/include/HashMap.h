#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t key;
    size_t value;
    bool filled;
} HashNode;

typedef struct {
    HashNode* array;
    size_t size;
    size_t capacity;
} HashMap;


HashMap* HashMap_create();
bool HashMap_has(HashMap* map, size_t key);
size_t HashMap_get(HashMap* map, size_t key);
void HashMap_set(HashMap* map, size_t key, size_t value);
void HashMap_remove(HashMap* map, size_t key);
void HashMap_destroy(HashMap* map);

#endif /* HASHMAP_H */