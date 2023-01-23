// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HID_DATA_STRUCTURES_H
#define HID_DATA_STRUCTURES_H
#include <cstdint>


enum connectionState { CONNECTION_NONE, CONNECTION_USB, CONNECTION_BLE };

enum connectionMode { CONNECTION_MODE_AUTO, CONNECTION_MODE_USB_ONLY, CONNECTION_MODE_BLE_ONLY };

struct HIDKeyboard {
    uint8_t modifier;
    uint8_t keycode[6];

      HIDKeyboard operator+(const HIDKeyboard& b) {
            HIDKeyboard c;
            c.modifier = this->modifier | b.modifier;
            int j = 0;
            for (int i = 0; i < 5; i++) {
                  if(this->keycode[i]>0)
                  {
                        c.keycode[i] = this->keycode[i];
                  }
                  else
                  {
                     c.keycode[i] = b.keycode[j];
                     j++;
                  }
            }
            return c;
      }

    bool operator!= (const HIDKeyboard &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDKeyboard &c2)
    {
          return  (keycode[0]==c2.keycode[0]) &&
                  (modifier==c2.modifier    ) &&
                  (keycode[1]==c2.keycode[1]) &&
                  (keycode[2]==c2.keycode[2]) &&
                  (keycode[3]==c2.keycode[3]) &&
                  (keycode[4]==c2.keycode[4]) &&
                  (keycode[5]==c2.keycode[5]) ;
              
    }
  } ;


struct HIDMouse {
    uint8_t buttons;
    int8_t x;
    int8_t y; 
    int8_t wheel; 
    int8_t pan;

      HIDMouse operator+(const HIDMouse& b) {
            HIDMouse c;
            c.buttons = this->buttons | b.buttons;
            c.x = this->x+b.x;
            c.y = this->y+b.y; 
            c.wheel = this->wheel + b.wheel; 
            c.pan = this->pan + b.pan;
            return c;
      }

    bool operator!= (const HIDMouse &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDMouse &c2)
    {
          return  (buttons==c2.buttons) &&
                  (x==c2.x) &&
                  (y==c2.y) &&
                  (wheel==c2.wheel) &&
                  (pan==c2.pan) ;       
    }    
  } ;


struct HIDConsumer {
    uint16_t usage_code;

      HIDConsumer operator+(const HIDConsumer& b) {
            HIDConsumer c;
            c.usage_code = (this->usage_code > b.usage_code)?this->usage_code:b.usage_code;
            return c;
      }

    bool operator!= (const HIDConsumer &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDConsumer &c2)
    {
          return  (usage_code==c2.usage_code);       
    }    
  } ;


struct HIDGamepad {
    int8_t x; 
    int8_t y;
    int8_t z;
    int8_t rz;
    int8_t rx;
    int8_t r;

      HIDGamepad operator+(const HIDGamepad& b) {
            HIDGamepad c;
            c.x  = this->x +b.x;
            c.y  = this->y +b.y; 
            c.z  = this->z +b.z; 
            c.rx = this->rx+b.rx;
            c.r  = this->r +b.r; 
            c.rz = this->rz+b.rz; 
            return c;
      }

    bool operator!= (const HIDGamepad &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDGamepad &c2)
    {
          return  (x==c2.x) &&
                  (y==c2.y) &&
                  (z==c2.z) &&
                  (rz==c2.rz) &&
                  (rx==c2.rx) &&
                  (r==c2.r) ;       
    }    
  } ;

#endif /* HID_DATA_STRUCTURES_H */
