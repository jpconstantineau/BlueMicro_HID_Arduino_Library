// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "hardware_detect.h"
#ifdef HARDWARE_DETECT_BLE_AVAILABLE
    #include <bluefruit.h>
    extern BLEDis bledis;
    extern BLEHidAdafruit blehid;
    void setupBLE(const char* manufacturer, const char* model, int8_t power, int8_t BLEProfile);
    void setupBLE(const char* manufacturer, const char* model, int8_t power);
    void startAdv(void);
    void set_keyboard_led(uint16_t conn_handle, uint8_t led_bitmap);
#endif
#endif
