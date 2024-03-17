#include "../include/Client.h"
#include "../include/Socket.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TPS 10
#define FIXED_TIMESTEP (1000000.0 / TPS)
#define MAX_CONNECTIONS 100

void Physics_update(double deltaTime)
{
}

void Game_update(double deltaTime)
{

    /* Send Client Buffers */
    for (size_t i = 0; i < clients->list->length; i++) {
        Client* client = (Client*)clients->list->array[i];

        if (client->outBuffer.index > 0) {
            ws_sendframe_bin(
                client->connection,
                (const char*)&client->outBuffer.bytes,
                client->outBuffer.index);
            client->outBuffer.index = 0;
        }
    }
}

void bye()
{
    printf("So long, suckers!\n");
}

int main()
{
    if (atexit(bye) != 0) {
        fprintf(stderr, "Failed to register cleanup function\n");
        return 1;
    }

    Socket_start();

    double deltaTime = 0.0;
    double then = 0.0;
    double now = clock();
    int isRunning = 1;

    while (isRunning) {
        now = clock();
        if (now - then >= FIXED_TIMESTEP) {
            deltaTime = (now - then) / 1000000.0;
            then = now;
            Physics_update(deltaTime);
            Game_update(deltaTime);
        }
    }

    return 0;
}