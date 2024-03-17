#ifndef PACKET_H
#define PACKET_H

#include "../include/Buffer.h"
#include "../include/Client.h"

void Packet_readFrom(Buffer* buffe, Client* client);

#endif /* PACKET_H */