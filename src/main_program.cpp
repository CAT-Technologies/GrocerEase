/*!
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
#include <chrono>
#include <cstdlib>
#include "cart.h"

using namespace std;

/***USED FOR TESTING***/
// #include <time.h>
// #include <unistd.h>

// static unsigned int microsecond = 1000000;

// float *feedAngle(float angleNflip_in[], int flip_test, float angle_new){
//     //cout << angle_new << "  ";
//     float angle = angle_new + flip_test*0.001;
//     if (angle >=180){
//         angle = 180;
//         flip_test = -flip_test;
//     }
//     if (angle <= 0){
//         angle = 0;
//         flip_test = -flip_test;
//     }
//     angleNflip_in[0] = angle;
//     angleNflip_in[1] = flip_test;
//     return angleNflip_in;
// }   
    
int main() {
  	/***INITIALIZE VARIABLES***/
    int a, b, c;                    //a: RSSI robot--phone, b: RSSI beacon--robot, c:vRSSI beacon--phone.
	float angle_old;		        //previous angle of the user.
	float angle_new;		        //current angle of the user.
    float angle_robot;              //current angle of the robot.
    float angle_diff;
	int followDistance = 1; 	    //the 'a' value the robot will try to maintain. Unit: metre.
	int angleMove = 15; 		    //angle to accumulate before moving. Unit: degrees.
    float a_distance;               //a converted into distance.
	int motorForward = 200;	        // !!--EDITABLE--!! default analog value to write to motor when moving forward. Range: 140-255.
	int motorLeft;			        //analog value to left motor.
	int motorRight;		            //analog value to right motor.
	int rotate = 0;		            //when rotate=1, robot rotates.
	int flip_cart = 1;		        //when flip_cart=1, angle is between 0 to 180. When flip_cart=-1, angle is between 0 to -180.
	int clockwise = 0;		        //when clockwise=1, user is assumed to be moving clockwise.
	int counterclockwise = 0;	    //when counterclockwise=1, user is assumed to be moving clockwise.
	int read_rotation = 1;		    //when read_rotation=1, reads user rotation: CW/CCW/Static
	int leftAmend;			        //correction to left motor speed.
	int rightAmend;		            //correction to right motor speed.
    int correction = 50;            // !!--EDITABLE--!! default motor speed correction. 
    int ir_left;                    //Left IR sensor.
    int ir_right;                   //Right IR sensor.
	double elapsed_time_ms = 0;	    //elapsed time.
	double timeRotate_right = 0;	//accumulated time where robot has rotated to the right whilst in forward motion.
	double timeRotate_left = 0;	    //accumulated time where robot has rotated to the left whilst in forward motion.
    double timeUserStatic = 0;      //accumulated time where user has not moved.
    Cart cart;
    cart.start();
    
    /***RSSI PART***/
    //initialize all angles based on the first received values of a, b, and c.
	a = receive_a();                //unit: dB
	b = receive_b();                //unit: dB
	c = receive_c();                //unit: dB
    cart.compute_angle(a,b,c);
	angle_new = cart.getAngle();
	angle_robot = angle_new;
	angle_old = angle_new;
    
    /***USED FOR TESTING***/
    // angle_new = -60;
	// angle_robot = 0;
    // //angle_robot = 0;
	// angle_old = angle_new;
    // a_distance = 1.5;
    // double runtime=0;
    // int run = 1;
    // float angleNflip_in[2];
	// float *angleNflip_out;
	// int flip_test = 1;
    // float angle_feed = angle_new;
    // int i=0;
    // angle_diff = 90;
     
	
    /***MAIN SECTION***/
	while (run == 1) {
      	//a = receive_a(); 		
      	//b = receive_b();
      	//c = receive_c();
	
	    auto t_start = std::chrono::high_resolution_clock::now();     //start time of the current loop
        cart.compute_angle(a,b,c);
      	angle_new = flip_cart*cart.getAngle();                          //!!--FUNCTION--!! Refer to calculate_angle()
        a_distance = cart.getDistance_a();                              //

        /***USED FOR TESTING: INCREASING ANGLES***/
        //angleNflip_out = feedAngle(angleNflip_in, flip_test, angle_feed);
        //angle_feed = angleNflip_out[0];
		//flip_test = angleNflip_out[1];
        //angle_new = flip_cart*angle_feed;
        
        //cout << "angle_new_in: " << angle_new << "  ";
        //cout << "angle_old_in: " << angle_old << "  ";
        //cout << "flip cart_in:" << flip_cart << "  ";
        
        /******SECTION A: WHEN ROBOT IS STILL WITHIN FOLLOW DISTANCE******/
        if (a_distance <= followDistance){
            
            /*ANGLE CORRECTION IF ROTATION FROM FORWARD MOTION HAS NOT BEEN COMPLETED (REFER TO SECTION B)*/
            //Function of this segment: estimates the amount of rotation --> adds to the current angle_robot --> resets accumulated time
            if (timeRotate_left > 0){
                angle_robot = cart.estimateRobotAngle(angle_robot, 0, -50, timeRotate_left);     //!!--FUNCTION--!! Refer to estimateRobotAngle()
                timeRotate_left = 0;
            }

            if (timeRotate_right > 0){
                angle_robot = cart.estimateRobotAngle(angle_robot, -50, 0, timeRotate_right);
                timeRotate_right = 0;
            }
            //cout << "read_rotation in :" << read_rotation << "  ";
            
            /*READ_CURRENT ROTATION*/
            //Function of this segment: Reads the current rotation of the user.
            if (read_rotation == 1){
                if (flip_cart == 1){
                    if (angle_new > angle_old){
                        clockwise = 1;
                        counterclockwise = 0;
                        read_rotation = 0;
                    }
                    else if (angle_new < angle_old){
                        clockwise = 0;
                        counterclockwise = 1;
                        read_rotation = 0;
                    }
                    else{
                        clockwise = 0;
                        counterclockwise = 0;
                        read_rotation = 1;
                    }
                    //read_rotation = 0;
                }
                else{
                    if (angle_new > angle_old){
                        clockwise = 0;
                        counterclockwise = 1;
                        read_rotation = 0;
                    }
                    else if (angle_new < angle_old){
                        clockwise = 1;
                        counterclockwise = 0;
                        read_rotation = 0;
                    }
                    else{
                        clockwise = 0;
                        counterclockwise = 0;
                        read_rotation = 1;
                    }
                    //read_rotation = 0;
                }
            }
            else{
            //frees up read_rotation if user remains static for more than 1 second.
                if (abs(angle_new - angle_old) < 1){
                    timeUserStatic = timeUserStatic + elapsed_time_ms;
                    if (timeUserStatic > 1000){
                        timeUserStatic = 0;
                        read_rotation = 1;
                    }
                }
                else{
                    timeUserStatic = 0;    
                }
            }
            /*RECOMPUTE angle_new WITH FLIPPING LOGIC*/
            //Function of this segment: conducts logical checks to deduce if a sign change is necessary.

            if (clockwise == 1){
            //Explanation: When user is heading in the clockwise direction, the angle should be increasing in the 0 to 180 degrees segment.
            //             If a decrease in angle is detected, flipping is conducted, thus changing the angle to the 0 to -180 degrees segment.
                if (angle_new < angle_old){
                    angle_new = -angle_new;
                    flip_cart = -flip_cartS;
                }
            }
            else if (counterclockwise == 1){
            //Explanation: When user is heading in the counterclockwise direction, the angle should be decreasing in the 0 to 180 degrees segment.
            //             If an increase in angle is detected, flipping is conducted, thus changing the angle to the 0 to -180 degrees segment.
                if (angle_new > angle_old){
                    angle_new = -angle_new;
                    flip_cart = -flip_cart;
                }
            }
        
            /*COMPUTE ANGLE DIFFERENCE*/
            //Function of this segment: dedicated to compute the angle difference between the robot and the user.
            //+ve value: CW, -ve: CCW
            angle_diff = angle_new - angle_robot;

            if (angle_diff > 180){
                angle_diff = angle_diff - 360;
            }
            else if (angle_diff < -180){
                angle_diff = angle_diff + 360;
            }
                
        
            /*DECIDE IF ROTATION WILL BE PERFORMED*/		
                if (rotate == 0 && abs(angle_diff) > angleMove){
                    rotate = 1;
                }
            else if (rotate == 0 && abs(angle_diff) < angleMove){
                    rotate = 0;
                    cart.writeMotor(0, 0); 
                }

            /*ROTATION*/
            if (rotate == 1){
                if (angle_diff > 0){
                    motorLeft = 255;                //!!--EDITABLE--!! Range: 0 to 255  !!NOTE: Minimum 140 to overcome the internal friction of the motor.
                    motorRight = -255;              //!!--EDITABLE--!! Range: 0 to -255 (-ve means the motor will rotate in the other direction.)
                }
                else if (angle_diff < 0){
                    motorLeft = -255;               //!!--EDITABLE--!! Range: 0 to -255
                    motorRight = 255;               //!!--EDITABLE--!! Range: 0 to 255
                }
                cart.writeMotor(motorLeft, motorRight);                                                            //!!--FUNCTION--!! Refer to writeMotor()
                angle_robot = cart.estimateRobotAngle(angle_robot, motorLeft, motorRight, elapsed_time_ms);        //!!--FUNCTION--!! Refer to estimateRobotAngle()

                
                if (abs(angle_robot-angle_new) < 0.1){
                //If current robot angle is equal to current angle of the user. (Tolerance 0.1 degrees !!--EDITABLE--!!)
                    rotate = 0; 		            //stops rotation   
                    cart.writeMotor(0, 0);                             
                }
            }
            
        }

        /******SECTION B: WHEN ROBOT IS OUTSIDE FOLLOW DISTANCE******/
        else if (a_distance > followDistance) {
            
            /*CONVERTS ANGLE DIFFERENCE BEFORE MOVING FORWARD TO TIME (REVERSE OF ANGLE CORRECTION IN SECTION A)*/
            if (angle_diff != 0){
                if (angle_diff > 0){
                   timeRotate_left = cart.angleToTime(angle_diff, 0, -correction);
                   angle_diff = 0;
                }
                else{
                   timeRotate_right = cart.angleToTime(angle_diff, -correction, 0);
                   angle_diff = 0;
                }
            }
            /*READS IR SENSOR*/
            ir_left = cart.get_leftIR();
            ir_right = cart.get_rightIR();
            
            //cout << ir_left << "  " << ir_right << "  ";

            /*ROTATION DUE TO OBSTACLE*/
            if (ir_left == 0 && ir_right == 1){
            //If obstacle is detected at left while robot is moving, moves to the right. Also, counts the time of the rotation to the right.
                leftAmend = 0;          //!!--EDITABLE--!!
                rightAmend = -correction;       //!!--EDITABLE--!!
                timeRotate_right = timeRotate_right + elapsed_time_ms;
            }

            else if (ir_left == 1 && ir_right == 0){
            //If obstacle is detected at right while robot is moving, moves to the left. Also, counts the time of the rotation to the left.
                leftAmend = -correction;        //!!--EDITABLE--!!
                rightAmend = 0;         //!!--EDITABLE--!!
                timeRotate_left = timeRotate_left + elapsed_time_ms;
            }
            else if (ir_left == 0 && ir_right == 0){
            //If obstacle is detected at both sides while robot is moving, moves to the left. Also, counts the time of the rotation to the left.
                leftAmend = -correction;        //!!--EDITABLE--!!
                rightAmend = 0;         //!!--EDITABLE--!!
                timeRotate_left = timeRotate_left + elapsed_time_ms;
            }
            else{
            //If no obstacles is detected, robot makes up the angle which it has rotated.
                if (timeRotate_right > 0){
                //If robot has rotated X seconds to the right, it tries to rotate X seconds back to the left.
                    leftAmend = -correction;    //!!--EDITABLE--!!
                    rightAmend = 0;             //!!--EDITABLE--!!
                    timeRotate_right = timeRotate_right - elapsed_time_ms;
                    if (timeRotate_right < 0){
                        timeRotate_right = 0;
                    }
                }
                else if (timeRotate_left > 0){
                //If robot has rotated X seconds to the left, it tries to rotate X seconds back to the right.
                    leftAmend = 0;              //!!--EDITABLE--!!
                    rightAmend = -correction;   //!!--EDITABLE--!!
                    timeRotate_left = timeRotate_left - elapsed_time_ms;
                    if (timeRotate_left < 0){
                        timeRotate_right = 0;
                    }
                }
                else{
                    leftAmend = 0;
                    rightAmend = 0;
                }
            }

            /*MOVES CART*/
            motorLeft = motorForward + leftAmend;
            motorRight = motorForward + rightAmend;
            cart.writeMotor(motorLeft, motorRight);
            angle_robot = angle_new;
            
            cout << motorLeft << "  " << motorRight << "  ";
        }
         
        else {
            cart.writeMotor(0, 0);
        }
        angle_old = angle_new;
        auto t_end = std::chrono::high_resolution_clock::now();
        elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        
        /**USED FOR TESTING**/
        // runtime = runtime + elapsed_time_ms;
        // //cout << "angle feed:" << angle_feed << "  ";
        // //cout << "angle new:" << angle_new << "  ";
        // //cout << "angle robot:" << angle_robot << "  ";
        // //cout << "angle diff:" << angle_diff << "  ";
        
        // //cout << "read_rotation out:" << read_rotation << "  ";
        // //cout << "clockwise:" << clockwise << "  ";
        // //cout << "counterclockwise:" << counterclockwise << "  ";
        // //cout << "flip cart:" << flip_cart << "  ";
        // cout << "\n";
        
        // //run = 0;
        // //i++;
        // if (runtime > 10000){
        // //if (i > 1000){
        //     run = 0;
        //     cart.stop();
        //     cout << "END!";
        // }
    }
}