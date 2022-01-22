// SPDX-FileCopyrightText: 2022 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HID_QUEUE_H
#define HID_QUEUE_H
#include "hardware_detect.h"
#include "bluetooth.h"
#include "usb.h"
#include <cstdint>
#include <vector>
#include <string.h>
#include <Arduino.h>
#include "hid_data_structures.h"
#include "hid_utils.h"

#ifndef HARDWARE_DETECT_BLE_AVAILABLE
  // Conversion table from Ascii to keycode (shift, keycode)
  // READ THIS: If you have a compile error here did you select TinyUSB for USB stack?
  const uint8_t hid_ascii_to_keycode[128][2] = { HID_ASCII_TO_KEYCODE };
  
  // Conversion table from Keycode to Ascii (ascii without shift, ascii with shift)
  const uint8_t hid_keycode_to_ascii[128][2] = { HID_KEYCODE_TO_ASCII };
#endif

class HID_Queues {
    public:
    HID_Queues();
    #ifdef HARDWARE_DETECT_BLE_AVAILABLE
      HID_Queues(BLEHidAdafruit* ble_hid);
    #endif
    #ifdef HARDWARE_DETECT_USB_AVAILABLE
      HID_Queues(Adafruit_USBD_HID* usb_hid);
      #ifdef HARDWARE_DETECT_BLE_AVAILABLE
        HID_Queues(Adafruit_USBD_HID* usb_hid, BLEHidAdafruit* ble_hid);
      #endif
    #endif
    

    void begin();

    void setBLEManufacturer(const char* manufacturer  );
    void setBLETxPower(int8_t power); // set power for this connection
    void setBLEModel(const char* model);
    void setHIDMessageDelay(int32_t delay);
    void setUSBPollInterval(uint8_t interval_ms);
    void setUSBStringDescriptor(const char *descriptor);
    
    // keyboard functions to add to queue
    void keyboardReport(HIDKeyboard* report);
    void keyboardReport(uint8_t modifier, uint8_t keycode[6]);
    void keyboardPress(char ch);
    void keyboardRelease();
    void keySequence(const char* str);

    // consumer functions to add to queue
    void consumerReport(HIDConsumer* report);
    void consumerReport(uint16_t usage_code);
    void consumerKeyPress(uint16_t usage_code);
    void consumerKeyRelease();

    // mouse functions to add to queue
    void mouseReport(HIDMouse* report);
    void mouseReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel, int8_t pan);
    void mouseButtonPress(uint8_t buttons);
    void mouseButtonRelease();
    void mouseMove(int8_t x, int8_t y);
    void mouseScroll(int8_t wheel);
    void mousePan(int8_t pan);

    // gamepad functions to add to queue
    //gamepadreportButtons(uint32_t button_mask);
    //gamepadreportHat(uint8_t hat);
    //gamepadreportJoystick(int8_t x, int8_t y, int8_t z, int8_t rz, int8_t rx, int8_t ry);

    // Functions to retreive from queues
    HIDKeyboard getKeyboardReport();
    HIDMouse getMouseReport();
    HIDConsumer getConsumerReport();
    HIDGamepad getGamepadReport();

    // Functions to see if queue has data
    bool isKeyboardQueueEmpty();
    bool isMouseQueueEmpty();
    bool isConsumerQueueEmpty();
    bool isGamepadQueueEmpty();

    // Empty queues from data
    void clearKeyboardQueue();
    void clearMouseQueue();
    void clearConsumerQueue();
    void clearGamepadQueue();

    #ifdef HARDWARE_DETECT_USB_AVAILABLE
        void processQueuesWithUSB();
    #endif
    #ifdef HARDWARE_DETECT_BLE_AVAILABLE
        void processQueuesWithBLE();
    #endif
    void processQueues(connectionMode mode);
    
    private:
    void addKeyboardReport(HIDKeyboard* report);
    void addMouseReport(HIDMouse* report);
    void addConsumerReport(HIDConsumer* report);
    void addGamepadReport(HIDGamepad* report);
    connectionState connection;
    
    const char* _model;
    const char* _manufacturer;
    const char* _descriptor;
    int8_t _power;
    int32_t _HIDMessageDelay;
    uint8_t _interval_ms;

    static std::vector<HIDKeyboard> keycode_queue;
    static std::vector<HIDMouse>    mouse_queue;
    static std::vector<HIDConsumer> consumer_queue;
    static std::vector<HIDGamepad>  gamepad_queue;
    #ifdef HARDWARE_DETECT_USB_AVAILABLE
      Adafruit_USBD_HID* usb_hid_driver;
    #endif
    #ifdef HARDWARE_DETECT_BLE_AVAILABLE
      BLEHidAdafruit* ble_hid_driver;
    #endif
    };

#endif /* HID_QUEUE_H */
