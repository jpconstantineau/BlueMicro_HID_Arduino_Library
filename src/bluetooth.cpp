// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "bluetooth.h"
#ifdef HARDWARE_DETECT_BLE_AVAILABLE
  BLEDis bledis;
  BLEHidAdafruit blehid;

void setupBLE(const char* manufacturer, const char* model, int8_t power)
{
  setupBLE( manufacturer,  model, power,0);
}

void setupBLE(const char* manufacturer, const char* model, int8_t power, int8_t BLEProfile)
{
  Bluefruit.begin();
  Bluefruit.setTxPower(power);    // Check bluefruit.h for supported values
  bledis.setManufacturer(manufacturer);
  Bluefruit.setName(model);
  bledis.setModel(model);
  

  if (BLEProfile > 0)
  {
    ble_gap_addr_t gap_addr;
    gap_addr = Bluefruit.getAddr();
    gap_addr.addr[0] += BLEProfile;
    Bluefruit.setAddr(&gap_addr);
  }


  bledis.begin();
  blehid.begin();
  blehid.setKeyboardLedCallback(set_keyboard_led);
  startAdv();
}

void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}



void set_keyboard_led(uint16_t conn_handle, uint8_t led_bitmap)
{
  (void) conn_handle;
  
  // light up Red Led if any bits is set
  if ( led_bitmap )
  {
    ledOn( LED_RED );
  }
  else
  {
    ledOff( LED_RED );
  }
}
#endif
