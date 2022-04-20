/*!
 * Copyright (C) 2022 Carry Assistant Trolley (C.A.T) Technologies
 *  
 * Adwait Naik 16.04.22
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 */

#include "cart_callback.h"

#include <iostream>

#include <cmath>

int count = 1;

// callback every 100ms
class DisplayAngleCallback: public Cart::CompAngleCallback {
  public: 
  // RSSI values for testing
  int a = -87;
  int b = -51;
  int c = -91;
  
  // offset values for testing
  static const int offset_a = 52;
  static const int offset_b = 52;
  static const int offset_c = 52;
  
  // stores updated angle
  float angle_updated;

  virtual void computeAngle(Cart & cart) {
    float d_a = pow(20, (a + offset_a));
    float d_b = pow(20, (b + offset_b));
    float d_c = pow(20, (c + offset_c));

    angle_updated = acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2)) / (2 * d_a * d_b));

    std::cout << "the updated angle is" << angle_updated;
  }
};

int main(int, char ** ) 
{
   Cart cart;
   DisplayAngleCallback displayAngleCallback;
   cart.regCompAngleCallback( & displayAngleCallback);
   cart.start();
   while (count) 
   {
      int ch = getchar();
      switch (ch) 
      {
         case 27:
                   count = 0;
                   break;
         default:
                   break;
      }
   }
   cart.stop();
}
