// SPDX-FileCopyrightText: 2022 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "bluemicro_hid.h"
#ifdef HARDWARE_DETECT_BLE_AVAILABLE
  #ifdef HARDWARE_DETECT_USB_AVAILABLE
    // BLE+USB
    HID_Queues bluemicro_hid (&usb_hid,&blehid);
  #else  
    // BLE ONLY
    HID_Queues bluemicro_hid (&blehid);
  #endif
#else  
  #ifdef HARDWARE_DETECT_USB_AVAILABLE
    // USB ONLY
    HID_Queues bluemicro_hid (&usb_hid);
  #else  
    // NO HID
    #error This library requires TinyUSB support and/or nRF52 BlueFruit support.
    ;
  #endif
#endif
