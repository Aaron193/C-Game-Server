#include "../include/Socket.h"
#include "../external/wsServer/include/ws.h"
#include "../include/Client.h"
#include "../include/EDict.h"
#include "../include/Packet.h"
#include <pthread.h>
#include <stdio.h>

#define PORT_NUMBER 8080
#define MESSAGE_BINARY 2
#define MAX_MESSAGE_SIZE 0xfff

EDict* clients = NULL;
HashMap* idMap = NULL;

struct ws_server_params {
    const char* host;
    int port;
    int thread_loop;
    int timeout_ms;
};

int id = 1;

/**
 * @brief This function is called whenever a new connection is opened.
 * @param client Client connection.
 */
void onopen(ws_cli_conn_t* client)
{
    printf("Client connected to the websocket\n");

    int next_id = id++;
    Client* c = Client_create(client, next_id);

    HashMap_set(idMap, (size_t)client, next_id);
    EDict_insert(clients, next_id, (size_t)c);
}

/**
 * @brief This function is called whenever a connection is closed.
 * @param client Client connection.
 */
void onclose(ws_cli_conn_t* client)
{
    printf("Client disconnected from the websocket\n");
    int id = (int)HashMap_get(idMap, (size_t)client);
    Client* c = (Client*)EDict_find(clients, id);
    EDict_remove(clients, id);

    free(c);
}

/**
 * @brief Message events goes here.
 * @param client Client connection.
 * @param msg    Message content.
 * @param size   Message size.
 * @param type   Message type.
 */
void onmessage(ws_cli_conn_t* connection, const unsigned char* msg, uint64_t size, int type)
{
    if (type != MESSAGE_BINARY) return;

    if (size > MAX_MESSAGE_SIZE) {
        printf("Message too big not accepting messages over 0xfff bytes\n");
        return;
    }

    int id = (int)HashMap_get(idMap, (size_t)connection);
    Client* client = (Client*)EDict_find(clients, id);
    Buffer* buffer = &client->inBuffer;

    Buffer_loadBuffer(buffer, (unsigned char*)msg, size);
    Packet_readFrom(buffer, client);
}

bool _isServerRunning = false;

void Socket_start()
{
    /**
        TODO: figure out when/if/where these should be freed
    */
    clients = EDict_create();
    idMap = HashMap_create();

    if (_isServerRunning) {
        printf("Trying to start server when already running!\n");
    }

    struct ws_server_params server_params = {
        .host = "localhost",
        .port = PORT_NUMBER,
        .thread_loop = 1,
        .timeout_ms = 1000,
    };

    ws_socket(&(struct ws_server) {
        .host = server_params.host,
        .port = server_params.port,
        .thread_loop = server_params.thread_loop,
        .timeout_ms = server_params.timeout_ms,
        .evs.onopen = &onopen,
        .evs.onclose = &onclose,
        .evs.onmessage = &onmessage,
    });

    _isServerRunning = true;
}