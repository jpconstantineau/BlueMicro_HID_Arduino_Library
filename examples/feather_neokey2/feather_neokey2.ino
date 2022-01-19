// SPDX-FileCopyrightText: 2021 BlueMicro_HID_Common contributors (https://github.com/jpconstantineau/BlueMicro_HID_Common/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include <BlueMicro_HID.h>

// This was tested with the following hardware:
// Adafruit nRF52832 Feather - BLE Only
// Adafruit nRF52840 Festher Express - BLE + USB
// Adafruit Feather RP2040 - USB Only
// Adafruit Feather M0 Express - USB Only
// Adafruit Feather M4 Express - USB Only 
// The GPIO/Pin differs betwen the feathers.
// No other changes are needed between Feathers.

const int pin = 7; // UserSw
bool activeState = false;


// the setup function runs once when you press reset or power the board
void setup()
{


  hid.begin(); 
  
  // Set up button, pullup opposite to active state
  pinMode(pin, activeState ? INPUT_PULLDOWN : INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("Adafruit TinyUSB HID Composite example");
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
    hid.mouseMove(delta, delta); // right + down
  }

  /*------------- Keyboard -------------*/
    // use to send key release report
    static bool has_key = false;

    if ( btn_pressed )
    {
      uint8_t keycode[6] = { 0 };
      keycode[0] = HID_KEY_A;

      hid.keyboardReport(0, keycode);

      has_key = true;
    }else
    {
      // send empty key report if previously has key pressed
      if (has_key) hid.keyboardRelease();
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
      hid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
      has_consumer_key = true;
    }else
    {
      // release the consume key by sending zero (0x0000)
      if (has_consumer_key) hid.consumerKeyRelease();
      has_consumer_key = false;
    }
    
  hid.processQueues(CONNECTION_MODE_AUTO);
}
