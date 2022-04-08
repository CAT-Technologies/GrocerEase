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

#include <memory>

#include <GPIO.hh>

extern "C" {
  #include <wiringPi.h>
}

using namespace std;

void GPIO::lw_Forward()
{
   digitalWrite(21, 1);
   digitalWrite(22, 0); 
}

void GPIO::lw_Backward()
{
   digitalWrite(21, 0);
   digitalWrite(22, 1); 
}

void GPIO::rw_Forward()
{
   digitalWrite(4, 1);
   digitalWrite(5, 0);   
}

void GPIO::rw_Backward()
{
   digitalWrite(4, 0);
   digitalWrite(5, 1);    
}

int main()
{
   int left_IR = 7;
   int right_IR = 16;
   
   wiringPiSetup();

   pinMode(21, OUTPUT);
   pinMode(22, OUTPUT);
   pinMode(23, PWM_OUTPUT);

   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(26, PWM_OUTPUT);

   pinMode(7, INPUT);
   pinMode(16, INPUT);

   while (1) 
   {
      int out1 = digitalRead(right_IR);
      int out2 = digitalRead(left_IR);
      cout << out1 << out2 << "\n";
   }
}