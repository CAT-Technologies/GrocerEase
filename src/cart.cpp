/*
 * Copyright (C) 2022 Carry Assistant Trolley (C.A.T) Technologies
 *  
 * Jia Wei Tan, April 11, 2022.
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

#include "cart.h"
#include <pigpio.h> 
#include <iostream>
#include <unistd.h>
#include <cmath>

void Cart::start(){
    if (gpioInitialise()<0) exit(1);

    /*left motor */
    gpioSetMode(en1, PI_INPUT);
    gpioSetMode(en2, PI_INPUT);
    gpioSetMode(motorL, PI_ALT0);

    /*right motor */
    gpioSetMode(en3, PI_INPUT);
    gpioSetMode(en4, PI_INPUT);
    gpioSetMode(motorR, PI_ALT0);

    gpioSetMode(left_IR, PI_INPUT);
    gpioSetMode(right_IR, PI_INPUT);
}

void Cart::stop(){
    writeMotor(0,0);
    gpioTerminate();
}

void Cart::lw_Forward(){
    gpioWrite(en1, 1);
    gpioWrite(en2, 0);
}

void Cart::rw_Forward(){
    gpioWrite(en3, 1);
    gpioWrite(en4, 0);
}

void Cart::lw_Backward(){
    gpioWrite(en1, 0);
    gpioWrite(en2, 1);
}

void Cart::rw_Backward(){
    gpioWrite(en3, 0);
    gpioWrite(en4, 1);
}

void Cart::writeMotor(int L, int R){
    /* L: Left Motor analog output
    * R: Right Motor analog output
    * range: -255 to 255
    */

    if (L >= 0) {
        lw_Forward();
    } else {
        lw_Backward();
    }

    if (R >= 0) {
        rw_Forward();
    } else {
        rw_Backward();
    }
    gpioPWM(motorL, abs(L));
    gpioPWM(motorR, abs(R));
}

void Cart::compute_angle(int a, int b, int c){
    d_a = pow(20, (a + offset_a));
    d_b = pow(20, (b + offset_b));
    d_c = pow(20, (c + offset_c));
}

float Cart::getAngle(){
    return acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));
}

float Cart::getDistance_a(){
    return d_a;
}

int Cart::get_leftIR(){
    return gpioRead(left_IR);
}

int Cart::get_rightIR(){
    return gpioRead(right_IR);
}

float Cart::estimateRobotAngle(float angle_old_robot, int rotation_left, int rotation_right, float timeStep){
    timeStep_s = timeStep*pow(10,-2);
    angle_new_robot = angle_old_robot + rocAngle*360*(rotation_left - rotation_right)/(510)*timeStep_s;

    if (angle_new_robot > 180){
	   angle_new_robot = angle_new_robot-360;
    }

	else if (angle_new_robot < -180){
	   angle_new_robot = angle_new_robot+360;
    }
    
    return angle_new_robot;
}

float Cart::angleToTime(float angle_diff, int rotation_left, int rotation_right){
    return abs(angle_diff*510/rocAngle/360/(rotation_left - rotation_right)*pow(10,2));
}
