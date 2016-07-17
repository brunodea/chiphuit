#pragma once

#include <stdint.h>

#define NUMBER_OF_INSTRS 0xFFFF
#define NUMBER_OF_GENREGS 15

using SReg = uint8_t;  // Simple Register
using DReg = uint16_t; // Double Register

using byte = uint8_t; // memory byte
using word = uint16_t;
