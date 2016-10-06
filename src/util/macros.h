#pragma once

#include <stdint.h>

#define MEMORY_SIZE_IN_BYTES 0x1000
#define MEMORY_ROM_START_ADDR 0x200

#define NUMBER_OF_INSTRS 0xFFFF
#define NUMBER_OF_GENREGS 15

#define WINDOW_WIDTH 64
#define WINDOW_HEIGHT 32

#define BITS_IN_BYTE 8

#define BYTES_IN_WIDTH (WINDOW_WIDTH / BITS_IN_BYTE)
#define BYTES_IN_HEIGHT WINDOW_HEIGHT

#define BYTES_IN_SCREEN BYTES_IN_WIDTH * BYTES_IN_HEIGHT

#define BYTES_IN_STACK 16 * 2

using SReg = uint8_t;  // Simple Register
using DReg = uint16_t; // Double Register

using byte = uint8_t; // memory byte
using word = uint16_t;

