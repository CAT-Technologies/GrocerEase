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


// a class to compute the RSSI angle for trilateration  
class ComputeAngle
{

   private:
   	
   	
   	// define what actually a, b,c stand for?
   	unsigned int a, b, c;
   	 	
      // define what actually d_a, d_b, d_c stand for?
   	float d_a, d_b, d_c;
   	
   	// finalise using cross calibration - done?
      // define what actually Offset_a, offset_b,c stand for?
   	static const int offset_a = -52;      
   	static const int offset_b = -52;
   	static const int offset_c = -52;
	   
      //define what actually N is and why 2, can we use macro or something better?
      static const int N ;
  
   	/// \brief angle.
   	float angle;

   public: 
	
      //constructor
      ComputeAngle()
      {
            a = 0;
            b = 0;
            c = 0;

            d_a = 0.0;
            d_b = 0.0;
            d_c = 0.0;

            N = 2;
            angle = 0.0;
      }

	/* Setter Function for RSSI values - to be improved using proper 
	   syntax/updates/callbacks   
      Use another class/interface to communicate/return these values ?? 
      Is it a setter/getter ? Do we need a getter callback - better?? */
	
	 void setRSSI(int a_dB, int b_dB, int c_dB)
	 {
		      a = a_dB;
		      b = b_dB;
		      c = c_dB;
	  }
	  
	 /* Function for computing distance using RSSI values
	    to be improved using proper syntax/callbacks 
       a,b,c double declaration again here in setRSSI and above unsigned int too
       Moreover, test with real values and dummy case  */
	  
	 void computeDistance()
	 {
         d_a = pow(10, ((offset_a - a)/(10*N)));  // 8/20 - 0.4 -- test values
         d_b = pow(10, ((offset_b - b)/(10*N)));  // 18/20 - 0.9
         d_c = pow(10, ((offset_c - c)/(10*N)));  // 38/20 - 1.9
    }
         
    /* Function for getting angle using distances - (write formula too)
	    to be improved using proper syntax/**callbacks - getters not allowed!** 
	    This might be needed by other GrocerEase class 
       is it actually a getter? */
         
   float getAngle()
   {
   	return acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));
   }
         
   /* Getting distance between Phone and Cart
	   Improve it using proper syntax/**callbacks - getters not allowed!** 
	   This might be needed by other GrocerEase class
      is it actually a getter?  */
         
   float get_a()
   {
      	return d_a*(pow(10,40));
   }
         
};


int main()
{


   ComputeAngle CompAng;

   CompAng.setRSSI(-60, -70, -90);

   /* CompAng.getAngle not working as expected probably
      test with proper values to get angle between a and b - check trilateration demo values*/

#ifdef DEBUG
   cout << "\n"<< "The distance a is : " << CompAng.get_a() << endl;
   cout << "The calculated angle is : "<< CompAng.getAngle() << endl;       
#endif

  /* add possible unit test after all these changes */
   
   return 0;
}
