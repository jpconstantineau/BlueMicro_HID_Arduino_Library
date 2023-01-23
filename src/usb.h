// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef USB_H
#define USB_H
#include "hardware_detect.h"
  #if defined HARDWARE_DETECT_USB_AVAILABLE
  #include "Adafruit_TinyUSB.h"
    // Report ID
    enum
    {
      RID_KEYBOARD = 1,
      RID_MOUSE,
      RID_CONSUMER_CONTROL, // Media, volume etc ..
    };
    
    // HID report descriptor using TinyUSB's template
    uint8_t const desc_hid_report[] =
    {
      TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(RID_KEYBOARD) ),
      TUD_HID_REPORT_DESC_MOUSE   ( HID_REPORT_ID(RID_MOUSE) ),
      TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(RID_CONSUMER_CONTROL) )
    };
  
  
    extern Adafruit_USBD_HID usb_hid;
    void setupUSB(uint8_t interval_ms, const char *descriptor);
  #endif
#endif
