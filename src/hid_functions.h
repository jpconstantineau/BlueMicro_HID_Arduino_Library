// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HID_FUNCTIONS_H
#define HID_FUNCTIONS_H
#include <cstdint>
#include <vector>
#include <numeric>
#include <algorithm>
#include "hid_types.h"
#include "hid_keycodes.h"
#include "hid_utils.h"

extern uint16_t keymap[] ;
const extern uint16_t  matrixsize;
const extern uint16_t  keymapsize;


// Standard Mapping Functions
uint8_t AddLayers(uint8_t layer, uint16_t keycode);
uint16_t  getKeycode(uint16_t pressedkey, uint8_t  layer);

trigger_keycodes_t processKeys(trigger_keys_t const activeKeys, trigger_keycodes_t &activeKeycodes, getkeycode_cb_t getKeycodefn, uint8_t  layer);
trigger_keycodes_t processKeys(trigger_keys_t const activeKeys, trigger_keycodes_t &activeKeycodes, getkeycode_cb_t getKeycodefn);
trigger_keycodes_t processKeys(trigger_keys_t const activeKeys, trigger_keycodes_t &activeKeycodes, uint8_t  layer);
trigger_keycodes_t processKeys(trigger_keys_t const activeKeys, trigger_keycodes_t &activeKeycodes);

uint8_t  getLayer(trigger_keys_t const activeKeys, addlayer_cb_t AddLayersFn, getkeycode_cb_t getKeycodefn);
uint8_t  getLayer(trigger_keys_t const activeKeys, addlayer_cb_t AddLayersFn);
uint8_t  getLayer(trigger_keys_t const activeKeys, getkeycode_cb_t getKeycodefn);
uint8_t  getLayer(trigger_keys_t const activeKeys);

#endif
