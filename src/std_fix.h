// SPDX-FileCopyrightText: 2021 BlueMicro_HID_Common contributors (https://github.com/jpconstantineau/BlueMicro_HID_Common/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef STD_FIX_H
#define STD_FIX_H
namespace std {
  void __throw_length_error(char const*) { while(true); }

  void __throw_bad_alloc() { while(true); }
}
#endif
