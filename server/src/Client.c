#include "../include/Client.h"
#include "../external/wsServer/include/ws.h"
#include "../include/Vec2.h"
#include <stdio.h>

#define NULL_CLIENT 0;

// currently unused

Client* Client_create(ws_cli_conn_t* connection, size_t id)
{
    Client* client = (Client*)malloc(sizeof(Client));
    if (client == NULL) {
        printf("Failed to allocate memory for client\n");
        exit(1);
    }

    client->connection = connection;
    client->cid = id;
    client->position = (Vec2) { 0, 0 };

    client->inBuffer.index = 0;
    client->inBuffer.size = 0xfff;

    client->outBuffer.index = 0;
    client->outBuffer.size = 0xfff;

    return client;
}