/*
 * Copyright (C) 2022 Carry Assistant Trolley (C.A.T) Technologies
 *  
 * Jia Wei Tan, February 16, 2022.
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

/*General Purpose Input Output for Raspberry Pi */

#ifndef GROCEREASE_H
#define GROCEREASE_H
#include <iostream>

class Grocerease
{

public:

    void initialize();

    void initialize_test(float angle_feed, float angle_robot_feed, float dist_a_feed); //  FOR TESTING

    void run_program();

    void run_program_test(float angle_feed, float dist_a_feed); //  FOR TESTING

    void stop();

    void read_RSSI();

    void write_newAngle();

    void write_a_distance();

    /**SECTION A**/
    void amendAngle();

    void readCurrentRotation();

    void angleRecompute();

    void angleDifference();

    void rotateDecision();

    void rotation();

    /**SECTION B**/
    void amendTime();

    void readIR();

    void ObstacleAvoidance();
    
    void printvar(); // FOR TESTING

public:
    double elapsed_time_ms;

private:
    int a, b, c;                                //a: RSSI robot--phone, b: RSSI beacon--robot, c:vRSSI beacon--phone.
    float angle_old;		                //previous angle of the user.
    float angle_new;		                //current angle of the user.
    float angle_robot;                          //current angle of the robot.
    float a_distance;                           //a converted into distance.
    float angle_diff;
    static const int followDistance = 1; 	//the 'a' value the robot will try to maintain. Unit: metre.
    static const int angleMove = 15; 		//angle to accumulate before moving. Unit: degrees.
    static const int motorForward = 255;	// !!--EDITABLE--!! default analog value to write to motor when moving forward. Range: 140-255.
    static const int correction = 100;          // !!--EDITABLE--!! default motor speed correction. 
    int motorLeft;			        //analog value to left motor.
    int motorRight;		                //analog value to right motor.
    int rotate = 0;		                //when rotate=1, robot rotates.
    int flip_cart = 1;		                //when flip_cart=1, angle is between 0 to 180. When flip_cart=-1, angle is between 0 to -180.
    int clockwise = 0;		                //when clockwise=1, user is assumed to be moving clockwise.
    int counterclockwise = 0;	                //when counterclockwise=1, user is assumed to be moving clockwise.
    int read_rotation = 1;		        //when read_rotation=1, reads user rotation: CW/CCW/Static
    int leftAmend;			        //correction to left motor speed.
    int rightAmend;		                //correction to right motor speed.
    int ir_left;                                //Left IR sensor.
    int ir_right;                               //Right IR sensor.
    double timeRotate_right = 0;	        //accumulated time where robot has rotated to the right whilst in forward motion.
    double timeRotate_left = 0;	                //accumulated time where robot has rotated to the left whilst in forward motion.
    double timeUserStatic = 0;                  //accumulated time where user has not moved.
    
};

#endif
