# BlueMicro_HID_Arduino_Library


[![Lint Library and Examples](https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/actions/workflows/lint.yaml/badge.svg)](https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/actions/workflows/lint.yaml) [![Current Version](https://img.shields.io/github/v/tag/jpconstantineau/BlueMicro_HID_Arduino_Library)](https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/tags)  [![GitHub pull requests](https://img.shields.io/github/issues-pr/jpconstantineau/BlueMicro_HID_Arduino_Library.svg)](https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library) [![GitHub issues](https://img.shields.io/github/issues/jpconstantineau/BlueMicro_HID_Arduino_Library.svg)](https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/issues)

A Universal Library for handling BLE and USB Human Interface Device (HID) with a computer.

## Supported Processors

| Controller | Core                      | Flash     | Ram   | HID         |
| ---------  | ------------------------  | --------- | ----- | ----------- |
| nRF52832   | 1 ARM Cortex M4F @ 64Mhz  | 512Kb     | 128Kb | BLE         |
| nRF52840   | 1 ARM Cortex M4F @ 64Mhz  | 1MB       | 256Kb | USB & BLE   |
| SAMD21     | 1 ARM Cortex M0+ @ 48Mhz  | 256Kb     | 32KBb | USB         |
| SAMD51     | 1 ARM Cortex M4F @ 120Mhz | 512Kb     | 192Kb | USB         |
| RP2040     | 2 ARM Cortex M0+ @ 133Mhz | up to 2Mb | 264Kb | USB         |


## Requirements for Support

- Arduino Board Support Package is available
- TinyUSB is used as the USB stack

# Examples

* `feather` - Simple test for barebones Feather boards
* `feather_neokey2` - Simple test for Feather boards with a NeoKey 2 Featherwing
* `itsybitsy` -  Simple test for ItsyBitsy boards
* `promicro` - Simple test for Boards with the form factor of a Pro Micro
* `qtpy` - Simple test for QT Py boards
* `rpipico` - Simple test for Raspberry Pi Pico

## Simple example

``` C++

#include <bluemicro_hid.h>

const int pin = 7; // UserSw
bool activeState = false;

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
```

# BlueMicro_HID API

The following API is available if the BlueMicro_HID library in included in a sketch file.

## hid.(...)

