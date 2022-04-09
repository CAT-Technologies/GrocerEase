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

float estimateRobotAngle(float angle_old_robot, int rotation_left, int rotation_right, float timeStep) {
  	/* Input:
   	 * angle_old_robot: initial heading angle of robot
  	 * rotation_left  : change in analog output to be written to left motor
  	 * rotation_right : change in analog output to be written to right motor
  	 * timeStep	  	: time since previous loop (unit: milisecond)
  	 *
  	 * Variable:
  	 * rocAngle	  	: rate of change of angle (rot/sec)
  	 *
  	 * Output:
 	 * angle_new	: updated angle of robot
 	 */
   
 	float rocAngle = 0.685557*360;
 	float timeStep_s = timeStep*pow(10,-3); 
  	float angle_new_robot = angle_old_robot + rocAngle*(rotation_left - rotation_right)/(510)*timeStep_s;

  	angle_new = angle_old + rocAngle*(rotation_left - rotation_right)/2048*timeStep;

	if (angle_new_robot > 180){
		angle_new_robot = angle_new_robot - 360;
	}

	else if (angle_new_robot < -180){
		angle_new_robot = angle_new_robot + 360;
   	}
   

  	return angle_new;
}

