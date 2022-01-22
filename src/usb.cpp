// SPDX-FileCopyrightText: 2022 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "usb.h"
#ifdef HARDWARE_DETECT_USB_AVAILABLE
  Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);
  void setupUSB(uint8_t interval_ms, const char *descriptor)
  {
    usb_hid.setPollInterval(interval_ms);
    usb_hid.setStringDescriptor(descriptor);
    usb_hid.begin();
  }
#endif
