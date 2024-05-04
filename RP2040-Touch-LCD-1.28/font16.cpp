/**
  ******************************************************************************
  * @file    font16.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text font16 for STM32xx-EVAL's LCD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fonts.h"

//
//  Font data for Courier New 12pt
//

const uint8_t Font16_Table[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3B, 0x80, 0x3B, 0x80, 0x3B, 0x80, 0x1B, 0x00, 0x13, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x08, 0x80, 0x08, 0x80, 0x18, 0x80, 0x19, 0x80, 0x7F, 0xC0, 0x11, 0x80, 0x11, 0x00, 0x11, 0x00, 0x31, 0x00, 0x7F, 0xC0, 0x33, 0x00, 0x22, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0C, 0x00, 0x0C, 0x00, 0x1F, 0x80, 0x31, 0x80, 0x71, 0xC0, 0x70, 0x00, 0x38, 0x00, 0x3E, 0x00, 0x0F, 0x80, 0x01, 0xC0, 0x00, 0xC0, 0x60, 0xC0, 0x71, 0xC0, 0x3F, 0x80, 0x0E, 0x00, 0x0E, 0x00,
0x00, 0x00, 0x30, 0x00, 0x78, 0x00, 0x4C, 0x00, 0x4C, 0x00, 0x4C, 0xC0, 0x79, 0x80, 0x06, 0x00, 0x0C, 0x00, 0x33, 0xC0, 0x46, 0x40, 0x06, 0x40, 0x06, 0x40, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x00, 0x31, 0x80, 0x30, 0x00, 0x30, 0x00, 0x18, 0x00, 0x38, 0x00, 0x6C, 0xC0, 0x67, 0xC0, 0x67, 0x80, 0x63, 0x00, 0x63, 0x80, 0x7E, 0xC0, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x80, 0x03, 0x80, 0x07, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x07, 0x00,
0x30, 0x00, 0x38, 0x00, 0x1C, 0x00, 0x06, 0x00, 0x06, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x07, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x3C, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x64, 0xC0, 0x7F, 0xC0, 0x0E, 0x00, 0x0A, 0x00, 0x1B, 0x00, 0x31, 0x80, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x7F, 0xC0, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x18, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x04, 0x00, 0x00, 0x00,
0x01, 0xC0, 0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x03, 0x00, 0x07, 0x00, 0x06, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x18, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x06, 0x00, 0x1E, 0x00, 0x3E, 0x00, 0x26, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x71, 0x80, 0x61, 0xC0, 0x01, 0xC0, 0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x0F, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xC0, 0x60, 0xC0, 0x71, 0x80, 0x3F, 0x80, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x39, 0x80, 0x31, 0x80, 0x61, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3F, 0x00, 0x3F, 0x80, 0x31, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x71, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x07, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x3A, 0x00, 0x3F, 0x80, 0x71, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xC0, 0x7F, 0xC0, 0x60, 0xC0, 0x61, 0x80, 0x01, 0x80, 0x03, 0x80, 0x03, 0x00, 0x07, 0x00, 0x06, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x61, 0xC0, 0x31, 0x80, 0x1F, 0x00, 0x3B, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x71, 0xC0, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x71, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0xC0, 0x3F, 0x80, 0x03, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x18, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x03, 0xC0, 0x1E, 0x00, 0x78, 0x00, 0x60, 0x00, 0x78, 0x00, 0x0F, 0x00, 0x03, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xC0, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xC0, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x78, 0x00, 0x1F, 0x00, 0x03, 0xC0, 0x00, 0xC0, 0x03, 0x80, 0x1E, 0x00, 0x78, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3C, 0x00, 0x3F, 0x00, 0x03, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x0F, 0x00, 0x0E, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x08, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0F, 0x00, 0x3F, 0x80, 0x70, 0xC0, 0x60, 0x40, 0x62, 0x40, 0x47, 0x40, 0x4C, 0xC0, 0x4C, 0x40, 0x4C, 0x40, 0x4C, 0x40, 0x4C, 0xC0, 0x47, 0x40, 0x60, 0x00, 0x60, 0x00, 0x30, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0A, 0x00, 0x1B, 0x00, 0x1B, 0x00, 0x1B, 0x00, 0x31, 0x80, 0x31, 0x80, 0x3F, 0x80, 0x3F, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7C, 0x00, 0x7F, 0x80, 0x61, 0x80, 0x61, 0xC0, 0x60, 0xC0, 0x61, 0x80, 0x7F, 0x00, 0x7F, 0x80, 0x61, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x61, 0xC0, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x70, 0xC0, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x70, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x06, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7C, 0x00, 0x7F, 0x00, 0x73, 0x80, 0x71, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x71, 0xC0, 0x73, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0xC0, 0x3F, 0xC0, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0xC0, 0x3F, 0xC0, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x67, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x21, 0x80, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x7F, 0xC0, 0x7F, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x61, 0x80, 0x73, 0x80, 0x3F, 0x00, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x00, 0x20, 0xC0, 0x70, 0xC0, 0x71, 0x80, 0x71, 0x80, 0x73, 0x00, 0x73, 0x00, 0x7E, 0x00, 0x7F, 0x00, 0x73, 0x00, 0x73, 0x80, 0x71, 0x80, 0x71, 0xC0, 0x70, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x7B, 0xC0, 0x6A, 0xC0, 0x6A, 0xC0, 0x6E, 0xC0, 0x64, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0xC0, 0x70, 0xC0, 0x78, 0xC0, 0x78, 0xC0, 0x68, 0xC0, 0x6C, 0xC0, 0x6C, 0xC0, 0x66, 0xC0, 0x66, 0xC0, 0x62, 0xC0, 0x63, 0xC0, 0x63, 0xC0, 0x61, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7E, 0x00, 0x7F, 0x80, 0x71, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x7F, 0xC0, 0x7F, 0x80, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x07, 0x00, 0x03, 0x80,
0x00, 0x00, 0x3E, 0x00, 0x7F, 0x80, 0x71, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x7F, 0x80, 0x7F, 0x00, 0x73, 0x00, 0x73, 0x00, 0x73, 0x80, 0x71, 0x80, 0x71, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x70, 0x00, 0x38, 0x00, 0x1F, 0x00, 0x0F, 0x80, 0x01, 0xC0, 0x00, 0xC0, 0x60, 0xC0, 0x71, 0xC0, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xC0, 0x7F, 0xC0, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x71, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0x80, 0x31, 0x80, 0x31, 0x80, 0x31, 0x00, 0x1B, 0x00, 0x1B, 0x00, 0x1B, 0x00, 0x0A, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xCE, 0x60, 0xCE, 0x60, 0x4A, 0x40, 0x4A, 0x40, 0x4A, 0x40, 0x4A, 0x40, 0x6A, 0xC0, 0x6A, 0xC0, 0x7B, 0xC0, 0x7B, 0xC0, 0x73, 0xC0, 0x71, 0x80, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x60, 0xC0, 0x71, 0xC0, 0x31, 0x80, 0x3B, 0x00, 0x1B, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x1B, 0x00, 0x33, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x60, 0xC0, 0x60, 0xC0, 0x71, 0xC0, 0x31, 0x80, 0x31, 0x80, 0x1B, 0x00, 0x1B, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x01, 0x80, 0x03, 0x80, 0x03, 0x00, 0x06, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x1C, 0x00, 0x18, 0x00, 0x30, 0x00, 0x30, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x0F, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0F, 0x00,
0x70, 0x00, 0x30, 0x00, 0x30, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x80, 0x01, 0x80, 0x01, 0x80,
0x1E, 0x00, 0x1E, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x1E, 0x00,
0x00, 0x00, 0x04, 0x00, 0x0E, 0x00, 0x0A, 0x00, 0x1B, 0x00, 0x1B, 0x00, 0x31, 0x80, 0x31, 0x80, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xC0,
0x1C, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x71, 0x80, 0x01, 0xC0, 0x0F, 0xC0, 0x3F, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x3E, 0xC0, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x76, 0x00, 0x6F, 0x80, 0x71, 0x80, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x71, 0x80, 0x6F, 0x80, 0x06, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x70, 0xC0, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x70, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x06, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x0D, 0xC0, 0x3E, 0xC0, 0x31, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x31, 0xC0, 0x3E, 0xC0, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x7F, 0xC0, 0x60, 0x00, 0x60, 0x00, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x07, 0xC0, 0x0F, 0xC0, 0x0C, 0x00, 0x0C, 0x00, 0x7F, 0xC0, 0x7F, 0xC0, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xC0, 0x3B, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x3A, 0xC0, 0x1E, 0xC0, 0x01, 0xC0, 0x01, 0x80, 0x1F, 0x80, 0x00, 0x00,
0x00, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x66, 0x00, 0x6F, 0x80, 0x71, 0x80, 0x71, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x3E, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0x80, 0x03, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x07, 0x00, 0x3E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0xC0, 0x31, 0xC0, 0x31, 0x80, 0x33, 0x00, 0x37, 0x00, 0x3E, 0x00, 0x37, 0x00, 0x33, 0x80, 0x31, 0x80, 0x31, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x80, 0x7F, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x64, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x6F, 0x80, 0x71, 0x80, 0x71, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x61, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x31, 0x80, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x7B, 0x80, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x70, 0xC0, 0x71, 0xC0, 0x6F, 0x80, 0x7F, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0xC0, 0x3B, 0xC0, 0x71, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x60, 0xC0, 0x71, 0xC0, 0x3E, 0xC0, 0x1E, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x3F, 0x80, 0x39, 0xC0, 0x30, 0xC0, 0x30, 0xC0, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x3F, 0x80, 0x71, 0xC0, 0x70, 0x00, 0x3C, 0x00, 0x1F, 0x80, 0x01, 0xC0, 0x00, 0xC0, 0x71, 0xC0, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x7F, 0xC0, 0x7F, 0xC0, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x31, 0x80, 0x31, 0x80, 0x3F, 0x80, 0x0E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xC0, 0x60, 0xC0, 0x71, 0xC0, 0x31, 0x80, 0x31, 0x80, 0x1B, 0x00, 0x1B, 0x00, 0x1B, 0x00, 0x0A, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x40, 0x4E, 0x40, 0x4A, 0x40, 0x4A, 0x40, 0x4A, 0x40, 0x6A, 0xC0, 0x6A, 0xC0, 0x7B, 0xC0, 0x3B, 0x80, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xC0, 0x31, 0x80, 0x3B, 0x80, 0x1B, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x1B, 0x00, 0x31, 0x80, 0x71, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xC0, 0x71, 0xC0, 0x31, 0x80, 0x39, 0x80, 0x1B, 0x00, 0x1B, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x7F, 0x80, 0x01, 0x80, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x03, 0xC0, 0x07, 0xC0, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x7E, 0x00, 0x7C, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x07, 0x00, 0x03, 0xC0,
0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00,
0x78, 0x00, 0x7C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0F, 0xC0, 0x07, 0xC0, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x1C, 0x00, 0x78, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xC0, 0x7C, 0xC0, 0x67, 0xC0, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};

sFONT Font16 = {
  Font16_Table,
  11, /* Width */
  16, /* Height */
};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
