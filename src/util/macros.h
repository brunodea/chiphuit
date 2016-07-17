#pragma once

#include <stdint.h>

#define MEMORY_SIZE_IN_BYTES 0x1000
#define MEMORY_ROM_START_ADDR 0x200

#define NUMBER_OF_INSTRS 0xFFFF
#define NUMBER_OF_GENREGS 15

using SReg = uint8_t;  // Simple Register
using DReg = uint16_t; // Double Register

using byte = uint8_t; // memory byte
using word = uint16_t;

