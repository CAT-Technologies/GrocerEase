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
#include <cmath>

 float calculate_angle(float a, float b, float c){
 /* a: RSSI robot--phone
  * b: RSSI beacon--robot
  * c: RSSI beacon--phone
  * offset_a: offset factor to max received signal of a
  * offset_b: offset factor to max received signal of b
  * offset_c: offset factor to max received signal of c
  * angle: beacon--robot--phone
  */
  
 /*Convert RSSI to distance*/
	d_a = pow(20,(a + off_a));
	d_b = pow(20,(b + off_b));
	d_c = pow(20,(c + off_c));
	
 /*Compute angle*/
	angle = acos((pow(d_a,2)+pow(d_b,2)-pow(d_c,2))/(2*d_a*d_b));
	return angle;
 }