// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "hid_functions.h"

/**************************************************************************************************************************/
// Standard Layer mapping Function
// conforms to addlayer_cb_t 
/**************************************************************************************************************************/
uint8_t AddLayers(uint8_t layer, uint16_t keycode) {
    uint8_t keyValue = static_cast<uint8_t>(keycode & 0x00FF);
    if (keyValue >= LAYER_0 && keyValue <= LAYER_F)
    {  
            //layer = layer | (1 << (keyValue - 0xF0)) ; // this is a mask
            layer = layer + (keyValue - LAYER_0) ; // this is a number
    }
    return layer;
} 

/**************************************************************************************************************************/
// Standard Matrix mapping Function
// conforms to getkeycode_cb_t
/**************************************************************************************************************************/
uint16_t  getKeycode(uint16_t pressedkey, uint8_t  layer)
{
  return ((pressedkey + layer * matrixsize)<keymapsize) ? keymap[pressedkey + layer * matrixsize] : 0; 
}

/**************************************************************************************************************************/
// Process Keys with Layers entered - custom matrix mapping
/**************************************************************************************************************************/
trigger_keycodes_t processKeys(trigger_keys_t const &activeKeys, trigger_keycodes_t &activeKeycodes, getkeycode_cb_t getKeycodefn, uint8_t  layer)
{
  //std::transform Needs #include <algorithm>
  std::transform(activeKeys.cbegin(), activeKeys.cend(), std::back_inserter(activeKeycodes),
                 [layer, getKeycodefn](uint16_t pressedkey) {return getKeycodefn(pressedkey, layer);} );  
  return activeKeycodes;
}
/**************************************************************************************************************************/
// Process Keys with No Layers entered - custom matrix mapping
/**************************************************************************************************************************/
trigger_keycodes_t processKeys(trigger_keys_t const &activeKeys, trigger_keycodes_t &activeKeycodes, getkeycode_cb_t getKeycodefn)
{
  uint8_t  layer = 0;
  return processKeys(activeKeys, activeKeycodes, getKeycodefn, layer);
}
/**************************************************************************************************************************/
// Process Keys with default matrix mapping - Layer entered 
/**************************************************************************************************************************/
trigger_keycodes_t processKeys(trigger_keys_t const &activeKeys, trigger_keycodes_t &activeKeycodes, uint8_t  layer)
{
  return processKeys(activeKeys, activeKeycodes, getKeycode, layer);
}
/**************************************************************************************************************************/
// Process Keys with No Layers entered - default matrix mapping 
/**************************************************************************************************************************/
trigger_keycodes_t processKeys(trigger_keys_t const &activeKeys, trigger_keycodes_t &activeKeycodes)
{
  uint8_t  layer = 0;
  return processKeys(activeKeys, activeKeycodes, getKeycode, layer);
}

/**************************************************************************************************************************/
// get Layer from pressed keys - custom matrix mapping - Custom Layer mapping
/**************************************************************************************************************************/
uint8_t  getLayer(trigger_keys_t const &activeKeys, addlayer_cb_t AddLayersFn, getkeycode_cb_t getKeycodefn)
{  
  trigger_keycodes_t triggerKeys;
  triggerKeys = processKeys(activeKeys,triggerKeys,getKeycodefn);  // get keycodes for layer 0
  // std::accumulate needs #include <numeric>
  return std::accumulate(triggerKeys.begin(), triggerKeys.end(), 0, AddLayersFn); 
}

/**************************************************************************************************************************/
// get Layer from pressed keys - Standard matrix mapping - Custom Layer mapping
/**************************************************************************************************************************/
uint8_t  getLayer(trigger_keys_t const &activeKeys, addlayer_cb_t AddLayersFn)
{
  return getLayer(activeKeys, AddLayersFn, getKeycode);
}

/**************************************************************************************************************************/
// get Layer from pressed keys - custom matrix mapping - Standard Layer mapping
/**************************************************************************************************************************/
uint8_t  getLayer(trigger_keys_t const &activeKeys, getkeycode_cb_t getKeycodefn)
{
  return getLayer(activeKeys, AddLayers, getKeycodefn);
}

/**************************************************************************************************************************/
// get Layer from pressed keys - Standard matrix mapping - Standard Layer mapping
/**************************************************************************************************************************/
uint8_t  getLayer(trigger_keys_t const &activeKeys)
{
  return getLayer(activeKeys, AddLayers, getKeycode);
}

