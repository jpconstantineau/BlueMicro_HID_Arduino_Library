# BlueMicro_HID_Arduino_Library
Universal BLE/USB HID Library

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