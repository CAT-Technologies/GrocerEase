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
#include <cstdlib>
using namespace std;

int main() {
/*initialize variables
 * a: RSSI robot--phone
 * b: RSSI beacon--robot
 * c: RSSI beacon--phone
 */
  int a, b, c;
  float angle_old = 0;
  float angle_new = 0;
  int followDistance = 1;    //unit: metre
  int angleMove = 15;        //angle to accumulate before moving
  int *rotation;
  int motorForward = 600;    
  int motorLeft = 0;
  int motorRight = 0;
  int rotate = 0;            /*used as a flag (corrects angle to 0 if already rotating
                              *waits for angle to accumulate if not*/

  while(1){
     a = receive_a();        //sent via pipes from other threads
     b = receive_b();
     c = receive_c();
   
     angle_new = calculate_angle(a, b, c);
     angle_diff = angle_new - angle_old;
      
     if (abs(angle_diff) > angleMove){
       rotate = 1;
     }
     else if (rotate == 0 && abs(angle_diff) < angleMove){
       angle_old = angle_old;                           //keeps old angle, does not rotate
     }
     
     while(rotate == 1){
       rotation = angleCorrection(angle_diff);          //linked to motor PWM output
       angle_old = calculateAngle(angle_old);           //Rotation to change in angle (needs to be tuned)
         
       if (angle_diff == 0){
         rotate = 0;                                    //stops angle correction                                      
        }
     }
     
     /*
      *rotation_L: rotation{0]
      *rotation_R: rotation[1]
      */
       
     if(a > followDistance){
       motorLeft = motorForward + rotation[0];
       motorRight = motorForward + rotation[1];
       writeMotor(motorLeft, motorRight);
     }
     else{
       motorLeft = rotation[0];
       motorRight = rotation[1];
       writeMotor(motorLeft, motorRight);
   }

}