// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "hid_queues.h"
#include "std_fix.h"

HID_Queues::HID_Queues()
{
    _HIDMessageDelay=2;
    _manufacturer="BlueMicro Industries";
    _model = "BlueMicro_NONE";
    _descriptor = "BlueMicro_DESC";
    _power=0;
    _interval_ms=2;
    connection = CONNECTION_NONE;

}

#ifdef HARDWARE_DETECT_BLE_AVAILABLE
  HID_Queues::HID_Queues(BLEHidAdafruit* ble_hid)
  {
    ble_hid_driver = ble_hid;
    _HIDMessageDelay=2;
    _power=0;
    _interval_ms=2;
    _manufacturer="BlueMicro Industries";
    _model = "BlueMicro_BLE";
    _descriptor = "BlueMicro_DESC";
    connection = CONNECTION_NONE;
  }
#endif

#ifdef HARDWARE_DETECT_USB_AVAILABLE
  HID_Queues::HID_Queues(Adafruit_USBD_HID* usb_hid)
  {
    usb_hid_driver = usb_hid;
    _HIDMessageDelay=2;
    _power=0;
    _interval_ms=2;
    _manufacturer="BlueMicro Industries";
    _model = "BlueMicro_USB";
    _descriptor = "BlueMicro_DESC";
    connection = CONNECTION_NONE;
  }

  #ifdef HARDWARE_DETECT_BLE_AVAILABLE
    HID_Queues::HID_Queues(Adafruit_USBD_HID* usb_hid, BLEHidAdafruit* ble_hid)
    {
      usb_hid_driver = usb_hid;
      ble_hid_driver = ble_hid;
      _HIDMessageDelay=10;
      _power=0;
      _interval_ms=2;
      _manufacturer="BlueMicro Industries";
      _model = "BlueMicro_HID";
      _descriptor = "BlueMicro_DESC";
      connection = CONNECTION_NONE;
    }
  #endif
#endif

void HID_Queues::begin()
{
  //reportvector.reserve(7);
  #ifdef HARDWARE_DETECT_USB_AVAILABLE
    setupUSB(_interval_ms, _descriptor);
  #endif
  #ifdef HARDWARE_DETECT_BLE_AVAILABLE
    setupBLE(_manufacturer, _model, _power);
  #endif
}

// cppcheck-suppress unusedFunction
void HID_Queues::setHIDMessageDelay(int32_t delay)
{
  _HIDMessageDelay = delay;
}

// cppcheck-suppress unusedFunction
void HID_Queues::setBLEManufacturer(const char* manufacturer)
{
  _manufacturer = manufacturer;
}

// cppcheck-suppress unusedFunction
void HID_Queues::setBLETxPower(int8_t power) 
{
  _power = power;
}

// cppcheck-suppress unusedFunction
void HID_Queues::setBLEModel(const char* model)
{
  _model = model;
}

// cppcheck-suppress unusedFunction
void HID_Queues::setUSBPollInterval(uint8_t interval_ms)
{
  _interval_ms=interval_ms;
}

// cppcheck-suppress unusedFunction
void HID_Queues::setUSBStringDescriptor(const char *descriptor)
{
  _descriptor=descriptor;
}

void HID_Queues::keyboardReport(HIDKeyboard* report)
{
  addKeyboardReport(report);
}

void HID_Queues::keyboardReport(uint8_t modifier, uint8_t keycode[6])
{
  HIDKeyboard report =
  {
      .modifier = modifier,
  };
  memcpy(report.keycode, keycode, 6);
  keyboardReport(&report);
}

void HID_Queues::keyboardPress(char ch)
{
  HIDKeyboard report;
  report.keycode[0] = 0;
  report.keycode[1] = 0;
  report.keycode[2] = 0;
  report.keycode[3] = 0;
  report.keycode[4] = 0;
  report.keycode[5] = 0;

  report.modifier = ( hid_ascii_to_keycode[(uint8_t)ch][0] ) ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
  report.keycode[0] = hid_ascii_to_keycode[(uint8_t)ch][1];
  keyboardReport(&report);
}

void HID_Queues::keyboardRelease()
{
  HIDKeyboard report;
  report.modifier = 0;
  report.keycode[0] = 0;
  report.keycode[1] = 0;
  report.keycode[2] = 0;
  report.keycode[3] = 0;
  report.keycode[4] = 0;
  report.keycode[5] = 0;
  keyboardReport(&report);
}

// cppcheck-suppress unusedFunction
void HID_Queues::keySequence(const char* str)
{
   // Send each key in sequence
  char ch;
  while( (ch = *str++) != 0 )
  {
    char lookahead = *str;
    keyboardPress(ch);

    /* Only need to empty report if the next character is NULL or the same with
     * the current one, else no need to send */
    if ( lookahead == ch || lookahead == 0 )
    {
      keyboardRelease();
    }
  }
}

void HID_Queues::consumerReport(HIDConsumer* report)
{
  addConsumerReport(report);
}

void HID_Queues::consumerReport(uint16_t usage_code)
{
  HIDConsumer report =
  {
      .usage_code = usage_code,
  };
  consumerReport(&report);
}

// cppcheck-suppress unusedFunction
void HID_Queues::consumerKeyPress(uint16_t usage_code)
{
  consumerReport(usage_code); 
}

// cppcheck-suppress unusedFunction
void HID_Queues::consumerKeyRelease()
{
  uint16_t code = 0;
  consumerReport(code); 
}

void HID_Queues::mouseReport(HIDMouse* report)
{
  addMouseReport(report);
}

void HID_Queues::mouseReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel, int8_t pan)
{
  HIDMouse report;
  report.buttons = buttons;
  report.x = x;
  report.y = y; 
  report.wheel = wheel; 
  report.pan = pan;
  mouseReport(&report); 
}

// cppcheck-suppress unusedFunction
void HID_Queues::mouseButtonPress(uint8_t buttons)
{
  mouseReport(buttons, 0, 0, 0, 0);
}

// cppcheck-suppress unusedFunction
void HID_Queues::mouseButtonRelease()
{
 mouseReport(0,0,0,0,0);
}

// cppcheck-suppress unusedFunction
void HID_Queues::mouseMove(int8_t x, int8_t y)
{
 mouseReport(0,x,y,0,0);
}

// cppcheck-suppress unusedFunction
void HID_Queues::mouseScroll(int8_t wheel)
{
 mouseReport(0, 0, 0, wheel,0) ;
}

// cppcheck-suppress unusedFunction
void HID_Queues::mousePan(int8_t pan)
{
  mouseReport(0, 0, 0, 0, pan);
}

HIDKeyboard HID_Queues::getKeyboardReport()
{
    HIDKeyboard reportdata  = keycode_queue.back();
    keycode_queue.pop_back();
    return reportdata;
}

HIDMouse HID_Queues::getMouseReport()
{
    HIDMouse reportdata  = mouse_queue.back();
    mouse_queue.pop_back();
    return reportdata;
}

HIDConsumer HID_Queues::getConsumerReport()
{
    HIDConsumer reportdata  = consumer_queue.back();
    consumer_queue.pop_back();
    return reportdata;
}

// cppcheck-suppress unusedFunction
HIDGamepad HID_Queues::getGamepadReport()
{
    HIDGamepad reportdata  = gamepad_queue.back();
    gamepad_queue.pop_back();
    return reportdata;
}
    
bool HID_Queues::isKeyboardQueueEmpty()
{
  return keycode_queue.empty();
}

bool HID_Queues::isMouseQueueEmpty()
{
  return mouse_queue.empty();
}

bool HID_Queues::isConsumerQueueEmpty()
{
  return consumer_queue.empty();
}

// cppcheck-suppress unusedFunction
bool HID_Queues::isGamepadQueueEmpty()
{
  return gamepad_queue.empty();
}

// cppcheck-suppress unusedFunction
void HID_Queues::clearKeyboardQueue()
{
    keycode_queue.clear();
}

// cppcheck-suppress unusedFunction
void HID_Queues::clearMouseQueue()
{
    mouse_queue.clear();
}

// cppcheck-suppress unusedFunction
void HID_Queues::clearConsumerQueue()
{
    consumer_queue.clear();
}

// cppcheck-suppress unusedFunction
void HID_Queues::clearGamepadQueue()
{
    gamepad_queue.clear();
}
#ifdef HARDWARE_DETECT_USB_AVAILABLE
void HID_Queues::processQueuesWithUSB()
{
  // Remote wakeup
  //if (( TinyUSBDevice.suspended() && ((!isMouseQueueEmpty()) || (!isKeyboardQueueEmpty()) || (!isConsumerQueueEmpty())) ))
  if ( TinyUSBDevice.suspended())
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    TinyUSBDevice.remoteWakeup();
  }
  if ( usb_hid_driver->ready() && !isMouseQueueEmpty())
  {
    HIDMouse ms_report;
    ms_report = getMouseReport();
    usb_hid_driver->mouseReport(RID_MOUSE, ms_report.buttons, ms_report.x, ms_report.y, ms_report.wheel, ms_report.pan);
    delay(_HIDMessageDelay);
  }
  if ( usb_hid_driver->ready() && !isKeyboardQueueEmpty())
  {
    HIDKeyboard kb_report;
    kb_report = getKeyboardReport();
    usb_hid_driver->keyboardReport(RID_KEYBOARD, kb_report.modifier, kb_report.keycode);
    delay(_HIDMessageDelay);
  }
  if ( usb_hid_driver->ready() && !isConsumerQueueEmpty())
  {
    HIDConsumer cs_report;
    cs_report = getConsumerReport();
    usb_hid_driver->sendReport16(RID_CONSUMER_CONTROL, cs_report.usage_code);
    delay(_HIDMessageDelay);
  }
}
#endif

#ifdef HARDWARE_DETECT_BLE_AVAILABLE
void HID_Queues::processQueuesWithBLE()
{
    if (  !isMouseQueueEmpty())
  {
    HIDMouse ms_report;
    ms_report = getMouseReport();
    ble_hid_driver->mouseReport(ms_report.buttons, ms_report.x, ms_report.y, ms_report.wheel, ms_report.pan);
    delay(_HIDMessageDelay);
  }
  if ( !isKeyboardQueueEmpty())
  {
    HIDKeyboard kb_report;
    kb_report = getKeyboardReport();
    ble_hid_driver->keyboardReport(kb_report.modifier, kb_report.keycode);
    delay(_HIDMessageDelay);
  }
  if ( !isConsumerQueueEmpty())
  {
    HIDConsumer cs_report;
    cs_report = getConsumerReport();
    ble_hid_driver->consumerReport(cs_report.usage_code);
    delay(_HIDMessageDelay);
  }
}
#endif

// cppcheck-suppress unusedFunction
void HID_Queues::processQueues(connectionMode mode)
{
  switch (mode)
  {
    case CONNECTION_MODE_BLE_ONLY:
        connection = CONNECTION_BLE;
    break;
    case CONNECTION_MODE_USB_ONLY:
        connection = CONNECTION_USB;
    break;
    case CONNECTION_MODE_AUTO:
        connection = CONNECTION_NONE;
        #ifdef HARDWARE_DETECT_BLE_AVAILABLE 
        if (Bluefruit.connected())
        {
          connection = CONNECTION_BLE;
        }
        #endif
        // if USB connected
        #ifdef HARDWARE_DETECT_USB_AVAILABLE  
        if (TinyUSBDevice.mounted())
        {
        connection = CONNECTION_USB;
        }
        #endif
    break;
    default:
    break;
  }

  switch(connection)
  {
    case CONNECTION_NONE:
    break;
    case CONNECTION_USB:
        #ifdef HARDWARE_DETECT_USB_AVAILABLE
          processQueuesWithUSB();
        #endif
    break;
    case CONNECTION_BLE:
        #ifdef HARDWARE_DETECT_BLE_AVAILABLE
        processQueuesWithBLE();
        #endif
    break;
    default:
    break;
    
  }
  
}

// PRIVATE FUNCTIONS
void HID_Queues::addKeyboardReport(HIDKeyboard* report)
{
  auto it = keycode_queue.begin();
  it = keycode_queue.insert(it, *report);   
}

void HID_Queues::addMouseReport(HIDMouse* report)
{
  auto it = mouse_queue.begin();
  it = mouse_queue.insert(it, *report);   
}

void HID_Queues::addConsumerReport(HIDConsumer* report)
{
  auto it = consumer_queue.begin();
  it = consumer_queue.insert(it, *report);   
}

// cppcheck-suppress unusedFunction
void HID_Queues::addGamepadReport(HIDGamepad* report)
{
  auto it = gamepad_queue.begin();
  it = gamepad_queue.insert(it, *report);   
}    


std::vector<HIDKeyboard> HID_Queues::keycode_queue;
std::vector<HIDMouse>    HID_Queues::mouse_queue;
std::vector<HIDConsumer> HID_Queues::consumer_queue;
std::vector<HIDGamepad>  HID_Queues::gamepad_queue;
