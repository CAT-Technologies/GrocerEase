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
   /// \brief angle.
   public: float angle;

   /// \brief a function to compute the angle.
   public: float find_angle(float a, float b, float c, 
                    float offset_a, float offset_b, float offset_c);
};

float ComputeAngle::find_angle(float a, float b, float c, 
                     float offset_a, float offset_b, float offset_c)
{
   float d_a = pow(20, (a + offset_a));
   float d_b = pow(20, (b + offset_b));
   float d_c = pow(20, (c + offset_c));

   float angle = 
      acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));
   return angle;
}

int main()
{
   ComputeAngle CompAng;
   float computed_angle;

   float a = -60.046;
   float b = -75.046;
   float c = -80.046;

   float offset_a = -15;
   float offset_b = -5;
   float offset_c = -0.75;

   computed_angle = CompAng.find_angle(a, b, c, offset_a, offset_b, offset_c);
   cout << "The computed angle is : " << computed_angle;
   return 0;
}
