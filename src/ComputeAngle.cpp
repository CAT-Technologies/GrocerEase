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

#include <cmath>

using namespace std;

/// \brief enable debug messages and error messages to stderr
#ifndef NDEBUG
#define DEBUG
#endif


/// \brief a class to compute the RSSI angle for trilateration  
class ComputeAngle
{

   public:
   /*! VARIABLES *
    * a: RSSI robot--phone
    * b: RSSI beacon--robot
    * c: RSSI beacon--phone
    * offset_a: RSSI received of a at 1 metre (!!TO BE RECALIBRATED)
    * offset_b: RSSI received of b at 1 metre (!!TO BE RECALIBRATED)
    * offset_c: RSSI received of c at 1 metre (!!TO BE RECALIBRATED)
    * d_a: a converted into distance (unit: metre)
    * d_b: b converted into distance (unit: metre)
    * d_c: c converted into distance (unit: metre)
    * N: broadcasting power value (Constant depends on the Environmental factor. Range 2–4)
    * angle: beacon--robot--phone
    */
   	   	
   	int a, b, c;
   	 	
   	float d_a, d_b, d_c;
   	
   	static const int offset_a = -52;      
   	static const int offset_b = -52;
   	static const int offset_c = -52;
      	static const int N = 3;
  
   	/// \brief angle.
   	float angle;

   public: 
	
      /// \brief brief description
      ComputeAngle()
      {
            a = 0;
            b = 0;
            c = 0;

            d_a = 0.0;
            d_b = 0.0;
            d_c = 0.0;

            angle = 0.0;
      }

	/*! Setter Function for RSSI values - to be improved using proper 
	   syntax/updates/callbacks   
      Use another class/interface to communicate/return these values ?? 
      Is it a setter/getter ? Do we need a getter callback - better?? */
	
	 void setRSSI(int a_dB, int b_dB, int c_dB)
	 {
		      a = a_dB;
		      b = b_dB;
		      c = c_dB;
	  }
	  
	 /*! Function for computing distance using RSSI values
	    to be improved using proper syntax/callbacks 
       a,b,c double declaration again here in setRSSI and above unsigned int too
       Moreover, test with real values and dummy case  */
	  
	 float computeDistance(float a, float b, float c)
	 {
         
         d_a = pow(10, ((offset_a - a)/(10*N)));  // 8/20 - 0.04 -- test values
         d_b = pow(10, ((offset_b - b)/(10*N)));  // 18/20 - 0.09
         d_c = pow(10, ((offset_c - c)/(10*N)));  // 38/20 - 0.19

         

         return acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));

    }
         
    /*! Function for getting angle using distances - (write formula too)
	    to be improved using proper syntax/**callbacks - getters not allowed!** 
	    This might be needed by other GrocerEase class 
       is it actually a getter? */
   /*      
   float getAngle()
   {
   	return acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));
   }
   */      
   /*! Getting distance between Phone and Cart
	   Improve it using proper syntax/**callbacks - getters not allowed!** 
	   This might be needed by other GrocerEase class
      is it actually a getter?  */
         
   float get_a(int d_a)
   {
      	return d_a*(pow(10,40));
   }
         
};


int main()
{
   ComputeAngle CompAng;

   //float a = CompAng.computeDistance(-60,-70,-50);
   cout << CompAng.offset_b - (-70) << endl;
   cout << CompAng.offset_c - (-50) << endl;
   cout << (pow(CompAng.d_a, 2) + pow(CompAng.d_b, 2) - pow(CompAng.d_c, 2))/(2 * CompAng.d_a * CompAng.d_b) << endl;
   //cout << a << endl;   
   cout << CompAng.d_a << " "<< CompAng.d_b <<" " << CompAng.d_c << endl;
   /*! CompAng.getAngle not working as expected probably
      test with proper values to get angle between a and b - check trilateration demo values*/

#ifdef DEBUG
   cout << "\n"<< "The distance a is : " << CompAng.get_a(CompAng.d_a) << endl;
   cout << "The calculated angle is : "<< CompAng.computeDistance(-60,-70,-50) << endl;       
#endif

  /*! add possible unit test after all these changes */
   
   return 0;
}
