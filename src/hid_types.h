
// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HID_TYPES_H
#define HID_TYPES_H

typedef std::vector <uint16_t> trigger_keycodes_t;
typedef std::vector <uint8_t>  trigger_keys_t;

// TypeDefs for mapping functions
typedef uint8_t (*addlayer_cb_t)(uint8_t layer, uint16_t keycode);
typedef uint16_t (*getkeycode_cb_t)(uint16_t pressedkey, uint8_t  layer);

#endif
