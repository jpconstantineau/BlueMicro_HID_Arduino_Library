// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HID_H
#define HID_H

#include "hardware_detect.h"
#include "bluetooth.h"
#include "usb.h"
#include "hid_queues.h"
#include "hid_keycodes.h"
extern HID_Queues bluemicro_hid;

typedef std::vector <uint16_t> trigger_keycodes_t;
typedef std::vector <uint8_t>  trigger_keys_t;
trigger_keycodes_t processKeys(trigger_keys_t activeKeys, trigger_keycodes_t activeKeycodes);
trigger_keycodes_t sendKeys(trigger_keycodes_t activeKeycodes);
#endif
