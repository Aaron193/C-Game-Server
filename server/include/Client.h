#include "../external/wsServer/include/ws.h"
#include "./Vec2.h"
#include "./Buffer.h"
#include <stdint.h>

typedef struct Client {
    ws_cli_conn_t* connection;
    uint16_t cid;
    Vec2 position;
    Buffer buffer;
} Client;
