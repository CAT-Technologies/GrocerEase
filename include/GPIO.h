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

namespace std
{
   /// \brief GPIO program to control the wheel rotation.
   class GPIO 
   {
      public: 

              /// \brief Constructor.
              GPIO();

              /// \brief Destructor.
              ~GPIO();

              /// \brief id left IR sensor output.
              int left_IR;

              /// \brief id right IR sensor output.
              int right_IR;

              /// \brief store the left IR sensor output.
              int out1;

              /// \brief store the right IR sensor output.
              int out2;

              /// \brief command to rotate the left forward wheel.
              void lw_Forward();

              /// \brief command to rotate the left backward wheel.
              void lw_Backward();

              /// \brief command to rotate the right forward wheel.
              void rw_Forward();

              /// \brief command to rotate the right backward wheel.
              void rw_Backward();

   };
}
