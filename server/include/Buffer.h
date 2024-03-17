#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    unsigned char bytes[0xfff];
    // unsigned char *bytes;
    size_t size;
    size_t index;
} Buffer;

Buffer* Buffer_create(unsigned char* bytes, size_t size);
void Buffer_destroy(Buffer* buffer);

void Buffer_loadBuffer(Buffer* buffer, unsigned char* bytes, size_t size);

uint8_t Buffer_r_ui8(Buffer* buffer);
uint16_t Buffer_r_ui16(Buffer* buffer);
uint32_t Buffer_r_ui32(Buffer* buffer);
float Buffer_r_f32(Buffer* buffer);
void Buffer_r_str(Buffer* buffer, char* out, uint16_t length);


void Buffer_w_ui8(Buffer* buffer, uint8_t value);
void Buffer_w_ui16(Buffer* buffer, uint16_t value);
void Buffer_w_ui32(Buffer* buffer, uint32_t value);
void Buffer_w_f32(Buffer* buffer, float value);
void Buffer_w_str(Buffer* buffer, char* value, uint16_t length);

#endif /* BUFFER_H */
