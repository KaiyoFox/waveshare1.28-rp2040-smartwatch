/*****************************************************************************
* | File        :   ImageData.C
* | Author      :  
* | Function    :   test Demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
******************************************************************************/

#include "ImageData.h"

const unsigned char Signal816[16] =  //mobie signal
  {
    0xFE, 0x02, 0x92, 0x0A, 0x54, 0x2A, 0x38, 0xAA, 0x12, 0xAA, 0x12, 0xAA, 0x12, 0xAA, 0x12, 0xAA
  };
const unsigned char Msg816[16] =  //message
  {
    0x1F, 0xF8, 0x10, 0x08, 0x18, 0x18, 0x14, 0x28, 0x13, 0xC8, 0x10, 0x08, 0x10, 0x08, 0x1F, 0xF8
  };

const unsigned char Bat816[16] =  //batery
  {
    0x0F, 0xFE, 0x30, 0x02, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x30, 0x02, 0x0F, 0xFE
  };

const unsigned char RunningPerson[32] = {  //16x16
  0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0xC0, 0x01, 0x80, 0x07, 0x80, 0x0F, 0xC0, 0x0B, 0xF0, 0x03, 0x10, 0x03, 0x80, 0x02, 0xC0, 0x06, 0xC0, 0x0C, 0xC0, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Sun[32] = {  //16x16
  0x01, 0x80, 0x03, 0xC0, 0x30, 0x0C, 0x27, 0xE4, 0x0F, 0xF0, 0x1F, 0xF8, 0x5F, 0xFA, 0xDF, 0xFB, 0xDF, 0xFB, 0x5F, 0xFA, 0x1F, 0xF8, 0x0F, 0xF0, 0x27, 0xE4, 0x30, 0x0C, 0x03, 0xC0, 0x01, 0x80
};

const unsigned char NoConnection[32] = {  //Phone with Cross //16x16
  0x0F, 0xF9, 0x10, 0x02, 0x10, 0x04, 0x10, 0x08, 0x10, 0x18, 0x10, 0x28, 0x10, 0x48, 0x10, 0x88, 0x11, 0x08, 0x12, 0x08, 0x04, 0x08, 0x08, 0x08, 0x10, 0x08, 0x31, 0x88, 0x50, 0x08, 0x8F, 0xF8
};

const unsigned char Connection[32] = {  //Phone //16x16
  0x0F, 0xF0, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x11, 0x88, 0x10, 0x08, 0x0F, 0xF0
};

const unsigned char Bluetooth88[8] =  // bluetooth
  { 0x18, 0x54, 0x32, 0x1C, 0x1C, 0x32, 0x54, 0x18 };

const unsigned char GPRS88[8] =  //GPRS
  {
    0xC3, 0x99, 0x24, 0x20, 0x2C, 0x24, 0x99, 0xC3
  };

const unsigned char Alarm88[8] =  //alram
  {
    0xC3, 0xBD, 0x42, 0x52, 0x4E, 0x42, 0x3C, 0xC3
  };
