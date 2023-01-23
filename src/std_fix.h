// SPDX-FileCopyrightText: 2022-2023 BlueMicro_HID_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef STD_FIX_H
#define STD_FIX_H
namespace std {
  void __throw_length_error(char const*) { while(true); }

  void __throw_bad_alloc() { while(true); }
}
#endif
