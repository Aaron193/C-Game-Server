#include "../include/Buffer.h"
#include "../include/Vec2.h"
#include <stdint.h>
#include <stdio.h>

enum NETWORK_HEADERS {
    SPAWN,
    MOVEMENT,
    MOUSE
};

void Packet_readFrom(Buffer* buffer)
{
    while (buffer->index < buffer->size) {
        uint8_t packetType = Buffer_r_ui8(buffer);
        switch (packetType) {
            case SPAWN: {
                uint8_t clientVersion = Buffer_r_ui8(buffer);
                uint16_t length = Buffer_r_ui16(buffer);
                char nickname[length + 1];
                nickname[length] = '\0';
                Buffer_r_str(buffer, nickname, length);

                printf("Spawn packet: [version]: %d  [nickname]: %s \n", clientVersion, nickname);

            } break;
            case MOVEMENT: {
                uint8_t direction = Buffer_r_ui8(buffer);
                Vec2 position = { 0, 0 };

                if (direction & 0x01) position.x = 1;
                if (direction & 0x02) position.x = -1;
                if (direction & 0x04) position.y = 1;
                if (direction & 0x08) position.y = -1;

            } break;
            case MOUSE: {
                uint32_t angle = Buffer_r_ui32(buffer);
            } break;
        }
    }
}