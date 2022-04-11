/*
 * Copyright (C) 2022 Carry Assistant Trolley (C.A.T) Technologies
 *  
 * Jia Wei Tan, February 26, 2022.
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

#include <iostream>
#include <cmath>

using namespace std;

/// \brief a class to compute the angle between two RSSI values.
class ComputeAngle
{
   private:
   
   int a, b, c;
   int offset_a = 62;
   int offset_b = 62;
   int offset_c = 62;
   float d_a, d_b, d_c;
   float angle;

   public:

   void setRSSI(int a_dB, int b_dB, int c_dB){
      a = a_dB;
      b = b_dB;
      c = c_dB;
   }

   void computeDistance(){
      d_a = pow(20, (a + offset_a));
      d_b = pow(20, (b + offset_b));
      d_c = pow(20, (c + offset_c));
   }

   float getAngle(){
      return acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));
   }

   float get_a(){
      return d_a;
   }
};

int main()
{
   ComputeAngle CompAng;

   CompAng.setRSSI(-52, -52, -52);

   cout << "The distance a is : " << CompAng.get_a;
   cout << "The calculated angle is : "<< CompAng.getAngle;
   return 0;
}
