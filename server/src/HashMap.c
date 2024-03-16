// #include "../include/ArrayList.h"
// #include <stdbool.h>

// // Hashmap <int, int> only (positive keys/values)

// typedef struct {
//     int key;
//     int value;
//     bool filled;
// } HashNode;

// typedef struct {
//     HashNode* array;
//     int size;
//     size_t capacity;
// } HashMap;

// HashMap* HashMap_create(size_t initialCapacity)
// {
//     HashMap* map = (HashMap*)malloc(sizeof(HashMap));
//     if (map == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     map->array = (HashNode*)malloc(initialCapacity * sizeof(HashNode));
//     if (map->array == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         free(map);
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < initialCapacity; ++i)
//         map->array[i].filled = false;

//     map->capacity = initialCapacity;
//     map->size = 0;

//     return map;
// }

// void _HashMap_resize(HashMap* map, size_t newCapacity)
// {
//     // printf("Resizing hashmap from %zu to %zu\n", map->capacity, newCapacity);
//     HashNode* newArray = (HashNode*)malloc(newCapacity * sizeof(HashNode));
//     if (newArray == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < newCapacity; ++i)
//         newArray[i].filled = false;

//     for (int i = 0; i < map->capacity; ++i) {
//         if (map->array[i].filled) {
//             int index = map->array[i].key % newCapacity;
//             while (newArray[index].filled)
//                 index = (index + 1) % newCapacity;

//             newArray[index] = map->array[i];
//         }
//     }

//     free(map->array);
//     map->array = newArray;
//     map->capacity = newCapacity;
// }

// float _HashMap_loadFactor(HashMap* map)
// {
//     return (float)map->size / map->capacity;
// }

// bool HashMap_has(HashMap* map, int key)
// {
//     int index = key % map->capacity;
//     while (map->array[index].filled) {
//         if (map->array[index].key == key)
//             return true;
//         index = (index + 1) % map->capacity;
//     }
//     return false;
// }

// int HashMap_get(HashMap* map, int key)
// {
//     int index = key % map->capacity;
//     while (map->array[index].filled) {
//         if (map->array[index].key == key)
//             return map->array[index].value;
//         index = (index + 1) % map->capacity;
//     }
//     return -1;
// }

// HashNode* _HashMap_getEntry(HashMap* map, int key)
// {
//     size_t index = key % map->capacity;
//     while (map->array[index].filled) {
//         if (map->array[index].key == key)
//             return &map->array[index];
//         index = (index + 1) % map->capacity;
//     }
//     return NULL;
// }

// void HashMap_set(HashMap* map, int key, int value)
// {
//     if (HashMap_has(map, key)) {
//         HashNode* entry = _HashMap_getEntry(map, key);
//         entry->value = value;
//         return;
//     }

//     // put item
//     size_t index = key % map->capacity;
//     while (map->array[index].filled)
//         index = (index + 1) % map->capacity;

//     map->array[index].key = key;
//     map->array[index].value = value;
//     map->array[index].filled = true;
//     map->size++;

//     // load factor
//     if (_HashMap_loadFactor(map) > 0.75) {
//         _HashMap_resize(map, map->capacity * 2);
//     }
// }

// void HashMap_remove(HashMap* map, int key)
// {
//     if (!HashMap_has(map, key))
//         return;

//     size_t index = key % map->capacity;
//     while (map->array[index].key != key)
//         index = (index + 1) % map->capacity;

//     map->array[index].filled = false;
//     map->size--;

//     // load factor
//     if (_HashMap_loadFactor(map) < 0.25) {
//         _HashMap_resize(map, map->capacity / 2);
//     }
// }

// // TEST
// // int main()
// // {
// //     HashMap* map = HashMap_create(5);

// //     // Insert key-value pairs
// //     HashMap_set(map, 1, 100);
// //     HashMap_set(map, 2, 200);
// //     HashMap_set(map, 3, 300);
// //     HashMap_set(map, 4, 400);
// //     HashMap_set(map, 5, 500); // Should resize the hashmap
// //     HashMap_set(map, 6, 600);

// //     // Retrieve values
// //     printf("Getting 1, expecting 100 : %d\n", HashMap_get(map, 1));
// //     printf("Getting 2, expecting 200 : %d\n", HashMap_get(map, 2));
// //     printf("Getting 3, expecting 300 : %d\n", HashMap_get(map, 3));
// //     printf("Getting 4, expecting 400 : %d\n", HashMap_get(map, 4));
// //     printf("Getting 5, expecting 500 : %d\n", HashMap_get(map, 5));
// //     printf("Getting 6, expecting 600 : %d\n", HashMap_get(map, 6));

// //     // Test resizing
// //     printf("Expecting capacity 10 : %d\n", map->capacity);

// //     // Test deletion
// //     HashMap_remove(map, 3);
// //     printf("Getting 3, expecting -1 : %d\n", HashMap_get(map, 3));
// //     printf("Expecting size 5: %d\n", map->size);

// //     // Test load factor after deletion
// //     printf("Expecting capacity 10 : %d\n", map->capacity);

// //     // Test load factor resizing down
// //     HashMap_remove(map, 4);
// //     HashMap_remove(map, 5);
// //     HashMap_remove(map, 6);
// //     printf("Expecting capacity 5 : %d\n", map->capacity);

// //     // Test load factor resizing up
// //     HashMap_set(map, 7, 700);
// //     HashMap_set(map, 8, 800);
// //     HashMap_set(map, 9, 900);
// //     HashMap_set(map, 10, 1000);
// //     printf("Expecting capacity 10 : %d\n", map->capacity);

// //     // Test collision handling
// //     HashMap_set(map, 100, 1000); // Should insert successfully
// //     printf("Getting 100, expecting 1000 : %d\n", HashMap_get(map, 100));

// //     for (int i = 0; i < 1000; i++) {
// //         HashMap_set(map, i, i);
// //     }
// //     for (int i = 0; i < 1000; i++) {
// //         HashMap_remove(map, i);
// //     }
// //     // Free memory
// //     free(map->array);
// //     free(map);
// //     return 0;
// // }