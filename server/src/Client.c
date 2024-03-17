#include "../include/Client.h"
#include "../external/wsServer/include/ws.h"
#include "../include/Vec2.h"
#include <stdio.h>

// currently unused

Client* Client_create(ws_cli_conn_t* connection)
{
    Client* client = (Client*)malloc(sizeof(Client));
    if (client == NULL) {
        printf("Failed to allocate memory for client\n");
        exit(1);
    }

    client->connection = connection;
    client->cid = 0;
    client->position = (Vec2) { 0, 0 };

    return client;
}