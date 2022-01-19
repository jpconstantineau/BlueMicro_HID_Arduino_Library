// SPDX-FileCopyrightText: 2021 BlueMicro_HID_Common contributors (https://github.com/jpconstantineau/BlueMicro_HID_Common/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "bluemicro_hid.h"
#ifdef HARDWARE_DETECT_BLE_AVAILABLE
  #ifdef HARDWARE_DETECT_USB_AVAILABLE
    // BLE+USB
    HID_Queues hid (&usb_hid,&blehid);
  #else  
    // BLE ONLY
    HID_Queues hid (&blehid);
  #endif
#else  
  #ifdef HARDWARE_DETECT_USB_AVAILABLE
    // USB ONLY
    HID_Queues hid (&usb_hid);
  #else  
    // NO HID
    ;
  #endif
#endif
