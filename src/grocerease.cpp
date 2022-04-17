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

/*General Purpose Input Outsput for Raspberry Pi */


#include "cart.h"
#include "grocerease.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
Cart cart;

void Grocerease::initialize()
{
    cart.start();
    read_RSSI();
    cart.compute_angle(a,b,c);
    angle_new = cart.getAngle();
    angle_robot = angle_new;
    angle_old = angle_new;
}

void Grocerease::initialize_test(float angle_feed, float angle_robot_feed, float dist_a_feed)
{
    cart.start();
    angle_new = angle_feed;
    angle_robot = angle_robot_feed;
    angle_old = angle_new;
    angle_diff = angle_new - angle_robot;
}

void Grocerease::run_program()
{ 
    read_RSSI();
    cart.compute_angle(a,b,c);
    write_newAngle();
    write_a_distance();

    if (a_distance <= followDistance)
    {
        amendAngle();
        readCurrentRotation();
        angleRecompute();
        angleDifference();
        rotateDecision();
        rotation();
    }
    else
    {
        amendTime();
        readIR();
        ObstacleAvoidance();
    }
    angle_old = angle_new;  
}

void Grocerease::run_program_test(float angle_feed, float dist_a_feed)
{ 
    
    angle_new = flip_cart*angle_feed;
    a_distance = dist_a_feed;

    if (a_distance <= followDistance)
    {
        amendAngle();
        readCurrentRotation();
        angleRecompute();
        angleDifference();
        rotateDecision();
        rotation();
    }
    else
    {
        amendTime();
        readIR();
        ObstacleAvoidance();
    }
    angle_old = angle_new;  
}

void Grocerease::stop()
{
    cart.stop();
}

void Grocerease::read_RSSI()
{
    //a = receive_a();
    //b = receive_b();
    //c = receive_c();
}

void Grocerease::write_newAngle()
{
    angle_new = flip_cart*cart.getAngle();
}

void Grocerease::write_a_distance()
{
    a_distance = cart.getDistance_a();
}

/**SECTION A**/
void Grocerease::amendAngle()
{
    if (timeRotate_left > 0)
    {
        angle_robot = cart.estimateRobotAngle(angle_robot, 0, -correction, timeRotate_left);
        timeRotate_left = 0;
    }

    if (timeRotate_right > 0)
    {
        angle_robot = cart.estimateRobotAngle(angle_robot, -correction, 0, timeRotate_right);
        timeRotate_right = 0;
    }
}

void Grocerease::readCurrentRotation()
{
    if (read_rotation == 1)
    {
        if (angle_new > angle_old)
        {
            clockwise = 1;
            counterclockwise = 0;
            read_rotation = 0;
        }
        else if (angle_new < angle_old)
        {
            clockwise = 0;
            counterclockwise = 1;
            read_rotation = 0;
        }
        else
        {
            clockwise = 0;
            counterclockwise = 0;
        }        
    }
    else{
        if (abs(angle_new - angle_old) < 1)
        {
            timeUserStatic = timeUserStatic + elapsed_time_ms;
            if (timeUserStatic > 1000)
            {
                timeUserStatic = 0;
                read_rotation = 1;
            }
        }
        else
        {
            timeUserStatic = 0;    
        }
    }
}

void Grocerease::angleRecompute()
{
     if (clockwise == 1 && (angle_new < angle_old))
    {
        angle_new = -angle_new;
        flip_cart = -flip_cart;
    }
    else if (counterclockwise == 1 && (angle_new > angle_old))
    {
        angle_new = -angle_new;
        flip_cart = -flip_cart;
    }
}

void Grocerease::angleDifference()
{
    angle_diff = angle_new - angle_robot;
    if (angle_diff > 180)
    {
        angle_diff = angle_diff - 360;
    }
    else if (angle_diff < -180)
    {
        angle_diff = angle_diff + 360;
    }
}

void Grocerease::rotateDecision()
{
    if (rotate == 0 && abs(angle_diff) > angleMove)
    {
        rotate = 1;
    }
    else if (rotate == 0 && abs(angle_diff) < angleMove)
    {
        rotate = 0;
        cart.writeMotor(0, 0); 
    }
}

void Grocerease::rotation()
{
    if (rotate == 1)
    {
        if (angle_diff > 0)
        {
            motorLeft = motorForward;                
            motorRight = -motorForward;              
        }
        else if (angle_diff < 0)
        {
            motorLeft = -motorForward;               
            motorRight = motorForward;               
        }                                                          
        angle_robot = cart.estimateRobotAngle(angle_robot, motorLeft, motorRight, elapsed_time_ms);

        if (abs(angle_robot-angle_new) < 0.1)
        {
            rotate = 0; 		              
            motorLeft = 0;
            motorRight = 0;                          
        }
        cart.writeMotor(motorLeft, motorRight);
    }
}

/**SECTION B**/
void Grocerease::amendTime()
{
    if (angle_diff != 0)
    {
        if (angle_diff > 0)
        {
            timeRotate_left = cart.angleToTime(angle_diff, 0, -correction);
            angle_diff = 0;
        }
        else
        {
            timeRotate_right = cart.angleToTime(angle_diff, -correction, 0);
            angle_diff = 0;
        }
    }
}

void Grocerease::readIR()
{
    ir_left = cart.get_leftIR();
    ir_right = cart.get_rightIR();
}

void Grocerease::ObstacleAvoidance()
{
    if (ir_left == 0 && ir_right == 1)
    {
        leftAmend = 0;
        rightAmend = -correction;
        timeRotate_right = timeRotate_right + elapsed_time_ms;
    }

    else if (ir_left == 1 && ir_right == 0)
    {
        leftAmend = -correction;
        rightAmend = 0;
        timeRotate_left = timeRotate_left + elapsed_time_ms;
    }

    else if (ir_left == 0 && ir_right == 0)
    {
        leftAmend = -correction;
        rightAmend = 0;
        timeRotate_left = timeRotate_left + elapsed_time_ms;
    }

    else
    {
        if (timeRotate_right > 0)
        {
            leftAmend = -correction;
            rightAmend = 0;
            timeRotate_right = timeRotate_right - elapsed_time_ms;
            if (timeRotate_right < 0)
            {
                timeRotate_right = 0;
            }
        }
        else if (timeRotate_left > 0)
        {
            leftAmend = 0;
            rightAmend = -correction;
            timeRotate_left = timeRotate_left - elapsed_time_ms;
            if (timeRotate_left < 0)
            {
                timeRotate_left = 0;
            }
        }
        else
        {
            leftAmend = 0;
            rightAmend = 0;
        }
    }
    motorLeft = motorForward + leftAmend;
    motorRight = motorForward + rightAmend;
    cart.writeMotor(motorLeft, motorRight);
    angle_robot = angle_new;
}

void Grocerease::printvar()
{
    std::cout << "angle new: " << angle_new << "  ";
    std::cout << "angle robot: " << angle_robot << "  ";
    std::cout << "L: " << motorLeft << "  ";
    std::cout << "R: " << motorRight << "  ";
    std::cout << "\n";
}
