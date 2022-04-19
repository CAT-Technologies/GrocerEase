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


int main() 
{

    grocerease.initialize();

    while(run)
    {
        auto t_start = std::chrono::high_resolution_clock::now();

        grocerease.run_program();
    
        auto t_end = std::chrono::high_resolution_clock::now();
        
        elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        grocerease.elapsed_time_ms = elapsed_time_ms;

    }
    cout << "Exited Program \n";
    grocerease.stop();
}
