#ifndef SOCKET_H
#define SOCKET_H

#include <pthread.h>
#include "../include/EDict.h"

void Socket_start();
extern EDict* clients;

#endif /* SOCKET_H */
