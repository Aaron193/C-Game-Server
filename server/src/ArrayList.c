// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct {
//     void** array;
//     size_t size;
//     size_t capacity;
//     size_t itemSize; // Size of each item in bytes
//     void (*printItem)(void*); // Function pointer to print individual items
//     void (*freeItem)(void*); // Function pointer to free individual items
// } ArrayList;

// ArrayList* ArrayList_create(size_t initialCapacity, size_t itemSize, void (*printItem)(void*), void (*freeItem)(void*))
// {
//     ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
//     if (list == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     list->array = (void**)malloc(initialCapacity * sizeof(void*));
//     if (list->array == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         free(list);
//         exit(EXIT_FAILURE);
//     }

//     list->size = 0;
//     list->capacity = initialCapacity;
//     list->itemSize = itemSize;
//     list->printItem = printItem;
//     list->freeItem = freeItem;

//     return list;
// }

// void ArrayList_append(ArrayList* list, void* element)
// {
//     if (list->size >= list->capacity) {
//         // Resize the array
//         list->capacity *= 2;
//         list->array = (void**)realloc(list->array, list->capacity * sizeof(void*));
//         if (list->array == NULL) {
//             fprintf(stderr, "Memory allocation failed\n");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Allocate memory for the new item and copy the data
//     void* newItem = (void*)malloc(list->itemSize);
//     if (newItem == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }
//     memcpy(newItem, element, list->itemSize);

//     // Add the new item to the array
//     list->array[list->size++] = newItem;
// }

// void ArrayList_deleteLast(ArrayList* list)
// {
//     if (list->size > 0) {
//         list->freeItem(list->array[list->size - 1]);
//         free(list->array[list->size - 1]);
//         list->size--;
//     }
// }

// void ArrayList_swapIndices(ArrayList* list, size_t index1, size_t index2)
// {
//     if (index1 < list->size && index2 < list->size) {
//         void* temp = list->array[index1];
//         list->array[index1] = list->array[index2];
//         list->array[index2] = temp;
//     }
// }

// void ArrayList_print(ArrayList* list)
// {
//     printf("ArrayList: ");
//     for (size_t i = 0; i < list->size; ++i) {
//         list->printItem(list->array[i]);
//         printf(" ");
//     }
//     printf("\n");
// }

// void ArrayList_destroy(ArrayList* list)
// {
//     // Free individual items and then the array
//     for (size_t i = 0; i < list->size; ++i) {
//         list->freeItem(list->array[i]);
//         free(list->array[i]);
//     }
//     free(list->array);
//     free(list);
// }

// // =====================TEST=====================

// // // Define a sample structure
// // typedef struct {
// //     int value;
// // } SampleItem;

// // // Function to print a sample item
// // void printSampleItem(void* item)
// // {
// //     SampleItem* sample = (SampleItem*)item;
// //     printf("%d", sample->value);
// // }

// // // Function to free a sample item
// // void freeSampleItem(void* item)
// // {
// //     free((SampleItem*)item);
// // }

// // int main()
// // {
// //     // Create an ArrayList of SampleItem
// //     ArrayList* list = ArrayList_create(5, sizeof(SampleItem), &printSampleItem, &freeSampleItem);

// //     // Append some SampleItems
// //     for (int i = 1; i <= 5; ++i) {
// //         SampleItem* newItem = (SampleItem*)malloc(sizeof(SampleItem));
// //         if (newItem == NULL) {
// //             fprintf(stderr, "Memory allocation failed\n");
// //             exit(EXIT_FAILURE);
// //         }
// //         newItem->value = i;
// //         ArrayList_append(list, newItem);
// //     }

// //     // Print the ArrayList
// //     ArrayList_print(list); // Output: ArrayList: 1 2 3 4 5
// //     // Delete the last item
// //     ArrayList_deleteLast(list);
// //     ArrayList_print(list); // Output: ArrayList: 1 2 3 4

// //     // Swap indices
// //     ArrayList_swapIndices(list, 0, 3);
// //     ArrayList_print(list); // Output: ArrayList: 4 2 3 1

// //     // Free memory
// //     ArrayList_destroy(list);

// //     return 0;
// // }
