#include "../external/wsServer/include/ws.h"
#include "../include/Socket.h"
#include <pthread.h>
#include <stdio.h>
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
}

int main()
{

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