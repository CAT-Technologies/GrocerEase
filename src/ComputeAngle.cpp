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

using namespace std;

// enable debug messages and error messages to stderr
#ifndef NDEBUG
#define DEBUG
#endif


/// \brief a class to compute the angle between two RSSI values.
class ComputeAngle
{

   private:
   	
   	unsigned int a, b, c;
   	 	
   	float d_a, d_b, d_c;
   	
   	//finalise using cross calibration
   	static const int offset_a = 62;      
   	static const int offset_b = 62;
   	static const int offset_c = 62;
  
   	/// \brief angle.
   	float angle;

   public: 
	
	/* Setter Function for RSSI values - to be improved using proper 
	   syntax/updates/callbacks   */
	
	 void setRSSI(int a_dB, int b_dB, int c_dB)
	 {
		      a = a_dB;
		      b = b_dB;
		      c = c_dB;
	  }
	  
	 /* Function for computing distance using RSSI values
	    to be improved using proper syntax/callbacks   */
	  
	 void computeDistance()
	 {
         d_a = pow(20, (a + offset_a));
         d_b = pow(20, (b + offset_b));
         d_c = pow(20, (c + offset_c));
    }
         
    /* Function for getting angle using distances - (write formula too)
	    to be improved using proper syntax/callbacks - getters not allowed! 
	    This might be needed by other GrocerEase class  */
         
   float getAngle()
   {
   	return acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));
   }
         
   /* Getting distance between Phone and Cart
	   Improve it using proper syntax/callbacks - getters not allowed! 
	   This might be needed by other GrocerEase class  */
         
   float get_a()
   {
      	return d_a;
   }
         
};


int main()
{


   ComputeAngle CompAng;

   CompAng.setRSSI(-52, -52, -52);

   /* CompAng.getAngle not working as expected probably */

#ifdef DEBUG
   cout << "\n"<< "The distance a is : " << CompAng.get_a() << endl;
   cout << "The calculated angle is : "<< CompAng.getAngle() << endl;       
#endif

   
   return 0;
}
