// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

  #ifdef ARDUINO_ARCH_NRF52 // includes both NRF52832_XXAA and NRF52840_XXAA 
    #define HARDWARE_DETECT_BLE_AVAILABLE
    #define HARDWARE_DETECTED
  #endif
  
  #ifdef USE_TINYUSB  
    #define HARDWARE_DETECT_USB_AVAILABLE
    #define HARDWARE_DETECTED
  #endif

#ifndef HARDWARE_DETECTED 
  #error This library requires TinyUSB support and/or nRF52 BlueFruit support.
#endif