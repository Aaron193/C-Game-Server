#include "../external/wsServer/include/ws.h"
#include "../include/Vec2.h"

// currently unused
typedef struct Client {
    ws_cli_conn_t* connection;
    int id;
    Vec2 position;

} Client;
