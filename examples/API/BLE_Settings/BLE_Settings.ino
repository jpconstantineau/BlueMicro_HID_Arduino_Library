// SPDX-FileCopyrightText: 2022 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

// This example show how to modify the BLE Settings
// Adafruit Feather with a NeoKey 2 FeatherWing
// Only 1 of the keys is used in this example
// You can use this example without a NeoKey 2
// Connect the "pin" to "GND". It's the one next to "SCL"
// 
// This example was tested with the following hardware:
//   Adafruit nRF52832 Feather - BLE Only
//   Adafruit nRF52840 Feather Express - BLE + USB
//   Adafruit Feather RP2040 - USB Only
//   Adafruit Feather M0 Express - USB Only
//   Adafruit Feather M4 Express - USB Only 
//
// Select the board 
// Select USB Stack: TinyUSB
// Select the port to upload to
// Compile and Upload
//

#include <bluemicro_hid.h>

// The Pin differs betwen the feathers.
// No other changes are needed between Feathers.
#ifdef ARDUINO_NRF52832_FEATHER
  const int pin = 27; 
  bool activeState = false;
#endif
#ifdef ARDUINO_NRF52840_FEATHER
  const int pin = 5; 
  bool activeState = false;
#endif
#ifdef ADAFRUIT_FEATHER_M0_EXPRESS
  const int pin = 5; 
  bool activeState = false;
#endif
#ifdef ADAFRUIT_FEATHER_M4_EXPRESS
  const int pin = 5; 
  bool activeState = false;
#endif
#ifdef ARDUINO_ADAFRUIT_FEATHER_RP2040
  const int pin = 7; 
  bool activeState = false;
#endif


// the setup function runs once when you press reset or power the board
void setup()
{
  bluemicro_hid.setBLEManufacturer("BlueMicro Industries");
  bluemicro_hid.setBLEModel("BlueMicro_HID");
  bluemicro_hid.setBLETxPower(4);
  bluemicro_hid.setHIDMessageDelay(10);
  bluemicro_hid.setUSBPollInterval(2);
  bluemicro_hid.setUSBStringDescriptor();
  //usb_hid.setReportCallback(NULL, hid_report_callback);
  //blehid.setKeyboardLedCallback(set_keyboard_led);
  bluemicro_hid.begin(); 
  
  // Set up button, pullup opposite to active state
  pinMode(pin, activeState ? INPUT_PULLDOWN : INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("BlueMicro_HID Composite example");
}

void loop()
{
  // poll gpio once each 10 ms
  delay(10);
  
  // Whether button is pressed
  bool btn_pressed = (digitalRead(pin) == activeState);

  /*------------- Mouse -------------*/
  if (btn_pressed )
  {
    int8_t const delta = 5;
    bluemicro_hid.mouseMove(delta, delta); // right + down
  }

  /*------------- Keyboard -------------*/
    // use to send key release report
    static bool has_key = false;

    if ( btn_pressed )
    {
      uint8_t keycode[6] = { 0 };
      keycode[0] = HID_KEY_A;

      bluemicro_hid.keyboardReport(0, keycode);

      has_key = true;
    }else
    {
      // send empty key report if previously has key pressed
      if (has_key) bluemicro_hid.keyboardRelease();
      has_key = false;
    }

    // Consumer Control is used to control Media playback, Volume, Brightness etc ...
    // Consumer report is 2-byte containing the control code of the key
    // For list of control check out https://github.com/hathach/tinyusb/blob/master/src/class/hid/hid.h

    // use to send consumer release report
    static bool has_consumer_key = false;

    if ( btn_pressed )
    {
      // send volume down (0x00EA)
      bluemicro_hid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
      has_consumer_key = true;
    }else
    {
      // release the consume key by sending zero (0x0000)
      if (has_consumer_key) bluemicro_hid.consumerKeyRelease();
      has_consumer_key = false;
    }
    
  bluemicro_hid.processQueues(CONNECTION_MODE_AUTO);
}