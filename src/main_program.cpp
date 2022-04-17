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
#include "grocerease.h"

using namespace std;
Grocerease grocerease;

int run = 1;
double elapsed_time_ms = 0;

// /**TEST**/
// float *feedAngle(float angleNflip_in[], int flip_test, float angle_new, int feedmode){
//     //cout << angle_new << "  ";
//     float angle = angle_new + feedmode*flip_test*0.001;
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
// /********/

int main() 
{
    // /**TEST**/
    // float angle_feed;
    // float angle_robot_feed;
    // float dist_a_feed;
    // float angleNflip_in[2];
	// float *angleNflip_out;
	// int flip_test = 1;
    // double runtime;
    // double totalruntime;
    // int userInp;
    // int anglefeedmode;
    
    // start:
    // cout << "initial angle: "; cin >> angle_feed;
    // cout << "initial angle_robot: "; cin >> angle_robot_feed;
    // cout << "dist_a (<1 or >1): "; cin >> dist_a_feed;
    // cout << "angle feed mode (1=CW, -1=CCW, 0=no change): "; cin >> anglefeedmode;
    // cout << "totalruntime (100 = 1s): "; cin >> totalruntime;
    
    
    // grocerease.initialize_test(angle_feed, angle_robot_feed, dist_a_feed);
    // /********/

    //grocerease.initialize();

    while(run)
    {
        auto t_start = std::chrono::high_resolution_clock::now();
        
        // /**TEST**/
        // angleNflip_out = feedAngle(angleNflip_in, flip_test, angle_feed, anglefeedmode);
        // angle_feed = angleNflip_out[0];
		// flip_test = angleNflip_out[1];
        // grocerease.run_program_test(angle_feed, dist_a_feed);
        // /********/

        grocerease.run_program();
    
        auto t_end = std::chrono::high_resolution_clock::now();
        
        elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        grocerease.elapsed_time_ms = elapsed_time_ms;

        // /**TEST**/
        // runtime = runtime + elapsed_time_ms;
        // grocerease.printvar();
        // if (runtime > totalruntime)
        // {
        //     cout << "again? (Y=1, N=0)"; cin >> userInp;
        //     if (userInp == 1)
        //     {
        //         goto start;
        //     }
        //     run = 0;
        // }
        // /********/
    }
    cout << "Exited Program \n";
    grocerease.stop();
}
