// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
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

static std::vector<uint8_t> reportvector;

/**************************************************************************************************************************/
// cppcheck-suppress unusedFunction
trigger_keycodes_t sendKeys(trigger_keycodes_t activeKeycodes)
{
 // Serial.println("S");
  static bool has_key = false;  // must be static to remember previous state
  if ( activeKeycodes.empty() )
    {
      // send empty key report if previously has key pressed
      if (has_key) 
      { 
        bluemicro_hid.keyboardRelease();
        has_key = false;
      }
    } 
    else
    {
        has_key = true;
        uint8_t currentMod = 0;
        for (auto keycode : activeKeycodes) 
        {
            auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);
            auto extraModifiers = static_cast<uint8_t>((keycode & 0xFF00) >> 8);
    
            if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)
            {
              // add hidKeycode to report vector
              reportvector.push_back(hidKeycode);
            }  
            //check if the hid keycode contains a modifier. // also check for macros.
            switch (hidKeycode) { 
                case KC_LCTRL:  currentMod |= 1;    currentMod |= extraModifiers; break;
                case KC_LSHIFT: currentMod |= 2;    currentMod |= extraModifiers; break;
                case KC_LALT:   currentMod |= 4;    currentMod |= extraModifiers; break;
                case KC_LGUI:   currentMod |= 8;    currentMod |= extraModifiers; break;
                case KC_RCTRL:  currentMod |= 16;   currentMod |= extraModifiers; break;
                case KC_RSHIFT: currentMod |= 32;   currentMod |= extraModifiers; break;
                case KC_RALT:   currentMod |= 64;   currentMod |= extraModifiers; break;
                case KC_RGUI:   currentMod |= 128;  currentMod |= extraModifiers; break;
            }
            //add all of the extra modifiers into the curren modifier 
            currentMod |= extraModifiers;
        }

        uint8_t keycode[6] = { 0 };
        uint8_t keycodeposition = 0;
        for (auto thiskeycode : reportvector) 
        {
          if (keycodeposition<6)
          {
              keycode[keycodeposition] = thiskeycode;
          }
          keycodeposition++;
        }
        bluemicro_hid.keyboardReport(currentMod, keycode);
        activeKeycodes.clear();
        reportvector.clear();
    }
  return activeKeycodes;
}
