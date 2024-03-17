#ifndef EDICT_H
#define EDICT_H

#include "./ArrayList.h"
#include "./HashMap.h"

typedef struct {
    ArrayList* list;
    HashMap* map;
} EDict;

EDict* EDict_create();
void EDict_insert(EDict* dict, size_t id, size_t address);
size_t EDict_find(EDict* dict, size_t id);
void EDict_remove(EDict* dict, size_t id);
void EDict_destroy(EDict* dict);

#endif /* EDICT_H */