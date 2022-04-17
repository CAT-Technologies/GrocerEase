/*!
 * Copyright (C) 2022 Carry Assistant Trolley (C.A.T) Technologies
 *  
 *
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

#ifndef CART_H
#define CART_H

#include <iostream>
#include <tuple>

#define ROC_ANGLE 0.685557
#define START_TIME 10 //ms

/**
 * Cart class to controls general movements of the robot cart
 */
class Cart
{
public:
        /**
        * Callback interface to compute the angle between
        * the RSSI values of a static beacon A
        * and the beacon B.
        */
        class CompAngleCallback
        {
        public:
               /**
                * Member function called to compute the angle
                * as and when the RSSI value changes.
                */ 
                virtual void computeAngle(Cart &) = 0;
        };

public:
        /**
         * Establishes the communication with the robot cart.
         * 
         * @param _defaultStartTime = START_TIME
         */
        void start(long _defaultStartTime=START_TIME);

        /**
         * Stops the comminucatio with the robot cart.
         */
        void stop();

        /**
         * Destroys the Cart object and ceases any communication.
         */
        ~Cart()
        {
            stop();
        }

        /** 
         * register callback computeAngle
         * @param _compAngleCallback A pointer to the callback interface
         */
        void regCompAngleCallback(CompAngleCallback *_compAngleCallback)
        {
            compAngleCallback = _compAngleCallback;
        }

        /** 
         * Rotates left wheel in the forward direction
         */
        void lw_Forward();

        /** 
         * Rotates right wheel in the forward direction
         */
        void rw_Forward();

        /** 
         * Rotates left wheel in  the backward direction
         */
        void lw_Backward();

        /** 
         * Rotates right wheel in the backward direction
         * 
         */
        void rw_Backward();

        /** 
         * Rotates the motors based on the analog outputs
         * ranging between -255 to 255
         * @param L: Left Motor analog output
         * @param L: Right Motor analog output
         */
        void writeMotor(int L, int R);

        /** 
         * Reads the left IR sensor.
         * @param left_IR: 4
         */
        int readLeftIRSensor(int left_IR);
        
        /** 
         * Reads the right IR sensor.
         * @param right_IR: 15
         */
        int readRightIRSensor(int left_IR);
        
        /** 
         * Estimates robot cart's angle at a time step.
         * @param angle_old_robot: robot's previous angle
         * @param rotation_left:  marks left rotation
         * @param rotation_right: martks right rotation
         * @param timeStep: indicates the time step 
         */
        float estimateRobotAngle(float angle_old_robot, int rotation_left, 
            int rotation_right, float timeStep);
        
        /** 
         * Estimates the time taken by the robot cart to rotate
         * based on the angle difference
         * @param angle_diff: difference between current and previous angles
         * @param rotation_left:  marks left rotation
         * @param rotation_right: martks right rotation
         */
        float angleToTime(float angle_diff, int rotation_left, 
            int rotation_right);

private:
    static const int left_IR = 4;
    static const int right_IR = 15;
    static const int motorL = 13;
    static const int motorR = 12;
    static const int en1 = 5;
    static const int en2 = 6;
    static const int en3 = 23;
    static const int en4 = 24;
    
    CompAngleCallback *compAngleCallback = nullptr;

    float d_a;
    float d_b;
    float d_c;
    float timeStep_s;
    float angle_new_robot;
};

#endif //CART_H
