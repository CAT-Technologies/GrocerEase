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

void writeMotor(int L, int R) {
  /* L: Left Motor analog output
   * R: Right Motor analog output
   * range: -1024 to 1024
   */

  if (L >= 0) {
    lw_Forward();
    pwmWrite(23, L);
  } else {
    lw_Backward();
    pwmWrite(23, -L);
  }

  if (R >= 0) {
    rw_Forward();
    pwmWrite(26, R);
  } else {
    rw_Backward();
    pwmWrite(26, -R);
  }

  return;
}
