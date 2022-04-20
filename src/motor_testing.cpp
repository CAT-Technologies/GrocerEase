/*
 * Copyright (C) 2022 Carry Assistant Trolley (C.A.T) Technologies
 *  
 * Jia Wei Tan, March 17, 2022.
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

#include "cart.h"
#include <iostream>
#include <unistd.h>

using namespace std;

static unsigned int microsecond = 1000000;

int main() 
{

    Cart cart;
    cart.start();

    int run = 1;
    int L = 0;
    int R = 0;

    while (run == 1) {

        cart.writeMotor(L, R);
        usleep(1 * microsecond);
        L = L+10;
        R = R+10;
        if(L>250){
        run = 0;
        }
    }
    cart.stop();
    
}
