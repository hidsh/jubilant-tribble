// File: include/zmk/drivers/analog_input.h

#ifndef ZMK_ANALOG_INPUT_H
#define ZMK_ANALOG_INPUT_H

#include <stdint.h>

int analog_input_read(uint8_t ch, int16_t *out);

#endif // ZMK_ANALOG_INPUT_H

