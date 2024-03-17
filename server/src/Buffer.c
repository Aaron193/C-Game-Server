#include "../include/Buffer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// typedef struct {
//     unsigned char bytes[0xfff];
//     size_t size;
//     size_t index;
// } Buffer;

// Buffer* Buffer_create(unsigned char* bytes, size_t size)
// {
//     if (size > 0xfff) {
//         printf("Buffer size too big\n");
//         exit(1);
//     }

//     Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
//     if (buffer == NULL) {
//         printf("Failed to allocate memory for buffer\n");
//         exit(1);
//     }

//     buffer->bytes = bytes;
//     buffer->size = size;
//     buffer->index = 0;
//     return buffer;
// }

void Buffer_loadBuffer(Buffer* buffer, unsigned char* bytes, size_t size)
{
    if (size > 0xfff) {
        printf("Buffer size too big\n");
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        buffer->bytes[i] = bytes[i];
    }

    buffer->size = size;
    buffer->index = 0;
}

void _Buffer_verifyBounds(Buffer* buffer, size_t size)
{
    if (buffer->index + size > buffer->size) {
        printf("Buffer overflow\n");
        exit(1);
    }
}

/* =================READ================= */

uint8_t Buffer_r_ui8(Buffer* buffer)
{
    _Buffer_verifyBounds(buffer, sizeof(uint8_t));

    uint8_t value = buffer->bytes[buffer->index++];
    return value;
}

uint16_t Buffer_r_ui16(Buffer* buffer)
{
    _Buffer_verifyBounds(buffer, sizeof(uint16_t));

    return buffer->bytes[buffer->index++] | (buffer->bytes[buffer->index++] << 8);
}

uint32_t Buffer_r_ui32(Buffer* buffer)
{
    _Buffer_verifyBounds(buffer, sizeof(uint32_t));

    return buffer->bytes[buffer->index++] | (buffer->bytes[buffer->index++] << 8) | (buffer->bytes[buffer->index++] << 16) | (buffer->bytes[buffer->index++] << 24);
}

float Buffer_r_f32(Buffer* buffer)
{
    _Buffer_verifyBounds(buffer, sizeof(float));

    union {
        uint32_t intValue;
        float floatValue;
    } converter;

    converter.intValue = ((buffer->index + 3) << 24) | ((buffer->index + 2) << 16) | ((buffer->index + 1) << 8) | buffer->index;
    buffer->index += 4;

    return converter.floatValue;
}

void Buffer_r_str(Buffer* buffer, char* out, uint16_t length)
{
    _Buffer_verifyBounds(buffer, length);

    for (uint16_t i = 0; i < length; ++i) {
        out[i] = buffer->bytes[buffer->index++];
    }
}

/* =================WRITE================= */

void Buffer_w_ui8(Buffer* buffer, uint8_t value)
{
    _Buffer_verifyBounds(buffer, sizeof(uint8_t));
    buffer->bytes[buffer->index++] = value;
}

void Buffer_w_ui16(Buffer* buffer, uint16_t value)
{
    _Buffer_verifyBounds(buffer, sizeof(uint16_t));

    buffer->bytes[buffer->index++] = value & 0xFF;
    buffer->bytes[buffer->index++] = (value >> 8) & 0xFF;
}

void Buffer_w_ui32(Buffer* buffer, uint32_t value)
{
    _Buffer_verifyBounds(buffer, sizeof(uint32_t));

    buffer->bytes[buffer->index++] = value & 0xFF;
    buffer->bytes[buffer->index++] = (value >> 8) & 0xFF;
    buffer->bytes[buffer->index++] = (value >> 16) & 0xFF;
    buffer->bytes[buffer->index++] = (value >> 24) & 0xFF;
}

void Buffer_w_f32(Buffer* buffer, float value)
{
    _Buffer_verifyBounds(buffer, sizeof(float));

    union {
        uint32_t intValue;
        float floatValue;
    } converter;

    converter.floatValue = value;
    buffer->bytes[buffer->index++] = (converter.intValue >> 24) & 0xFF;
    buffer->bytes[buffer->index++] = (converter.intValue >> 16) & 0xFF;
    buffer->bytes[buffer->index++] = (converter.intValue >> 8) & 0xFF;
    buffer->bytes[buffer->index++] = converter.intValue & 0xFF;
}

// length = byte-length
void Buffer_w_str(Buffer* buffer, char* value, uint16_t length)
{
    _Buffer_verifyBounds(buffer, length);

    for (size_t i = 0; i < length; ++i) {
        buffer->bytes[buffer->index++] = value[i];
    }
}

void Buffer_destroy(Buffer* buffer)
{
    free(buffer);
}