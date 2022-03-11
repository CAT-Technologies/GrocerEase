/*
 * Copyright (C) 2022 Carry Assistant Trolley (C.A.T) Technologies
 *  
 * Jia Wei Tan, March 11, 2022.
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

float estimateRobotAngle(float angle_old, int rotation_left, int rotation_right) {
  /* Input:
   * angle_old	  : initial heading angle of robot
   * rotation_left  : change in analog output to be written to left motor
   * rotation_right : change in analog output to be written to right motor
   *
   * Variable:
   * rocAngle	  : rate of change of angle (!!)_VARIABLE TO BE TUNED_(!!)
   *
   * Output:
   * angle_new	  : updated angle of robot
   */
   
   float rocAngle = ...;

   angle_new = angle_old + rocAngle*(rotation_left - rotation_right)/2048*timeStep; 
   

  return angle_new;
}
