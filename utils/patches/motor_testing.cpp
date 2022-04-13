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

/*General Purpose Input Output for Raspberry Pi */

#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <pigpio.h> 

using namespace std;

static unsigned int microsecond = 1000000;

//Left forward wheel
void lw_Forward() {
  gpioWrite(5, 1);
  gpioWrite(6, 0);
}

//Right forward wheel
void rw_Forward() {
  gpioWrite(23, 1);
  gpioWrite(24, 0);
}

//Left backward wheel
void lw_Backward() {
  gpioWrite(5, 0);
  gpioWrite(6, 1);
}

//Right forward wheel
void rw_Backward() {
  gpioWrite(23, 0);
  gpioWrite(24, 1);
}

void writeMotor(int L, int R) {
  /* L: Left Motor analog output
   * R: Right Motor analog output
   * range: -255 to 255
   */

  if (L >= 0) {
    lw_Forward();
  } else {
    lw_Backward();
  }

  if (R >= 0) {
    rw_Forward();
  } else {
    rw_Backward();
  }
  gpioPWM(13, abs(L));
  gpioPWM(12, abs(R));
  cout << L << R << "\n";
  return;
}

int main() {
  int left_IR = 4;
  int right_IR = 15;
  
  if (gpioInitialise()<0) exit(1);

  /*left motor */
  gpioSetMode(5, PI_INPUT);
  gpioSetMode(6, PI_INPUT);
  gpioSetMode(13, PI_ALT0);

  /*right motor */
  gpioSetMode(23, PI_INPUT);
  gpioSetMode(24, PI_INPUT);
  gpioSetMode(12, PI_ALT0);

  gpioSetMode(left_IR, PI_INPUT);
  gpioSetMode(right_IR, PI_INPUT);
  
  int run = 1;
  int L = 0;
  int R = 0;
  while (run == 1) {
   // writeMotor(128, 128);
   // sleep(3 * microsecond); 
    writeMotor(L, R);
    sleep(1 * microsecond);   //replaced by usleep by sleep - to be tested
    L = L+10;
    R = R+10;
    if(L>250){
    run = 0;
    }
  }
  writeMotor(0, 0);
  gpioTerminate();
}
