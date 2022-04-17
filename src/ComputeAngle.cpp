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
	    and then using it to calculate angle  */
	  
	 pair<float, float> computeAngleRSSI(float a, float b, float c)
	 {
         
         d_a = pow(10, ((offset_a - a)/(10*N)));
         d_b = pow(10, ((offset_b - b)/(10*N)));  
         d_c = pow(10, ((offset_c - c)/(10*N)));  

         float followAngle = acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2))/(2 * d_a * d_b));

         return make_pair(followAngle, d_a);
    }
     
   /*! Getting distance between Phone and Cart */
         
   float get_a(float d_a)
   {
      	return d_a;
   }
         
};


int main()
{
   ComputeAngle CompAng;

   pair<float, float> details = CompAng.computeAngleRSSI(-55,-55,-50);

   cout << "The calculated angle is : "<< details.first << endl;
   cout << "The calculated follow distance is : "<< details.second << endl;       
     

   return 0;
}
