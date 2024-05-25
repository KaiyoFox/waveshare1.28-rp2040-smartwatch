/**
  ******************************************************************************
  * @file    Font8.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text Font8 for STM32xx-EVAL's LCD driver. 
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

const uint8_t Font8_Table[] = {
  //space
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //exclam
  0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
  //quotedbl
  0x50, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //numbersign
  0x00, 0x20, 0x78, 0x50, 0xF8, 0x40, 0x00, 0x00,
  //dollar
  0x20, 0x50, 0x40, 0x60, 0x10, 0x50, 0x20, 0x00,
  //percent
  0x00, 0x90, 0x80, 0x20, 0x18, 0x48, 0x00, 0x00,
  //ampersand
  0x00, 0x50, 0x50, 0x60, 0xA8, 0x90, 0x00, 0x00,
  //quotesingle
  0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //parenleft
  0x10, 0x20, 0x00, 0x40, 0x40, 0x00, 0x20, 0x10,
  //parenright
  0x40, 0x20, 0x20, 0x00, 0x00, 0x20, 0x20, 0x40,
  //asterisk
  0x00, 0x20, 0x78, 0x10, 0x10, 0x00, 0x00, 0x00,
  //plus
  0x00, 0x00, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00,
  //comma
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40,
  //hyphen
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //period
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00,
  //slash
  0x00, 0x10, 0x00, 0x20, 0x20, 0x00, 0x40, 0x00,
  //zero
  0x00, 0x50, 0x10, 0x20, 0x40, 0x50, 0x20, 0x00,
  //one
  0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
  //two
  0x00, 0x10, 0x10, 0x10, 0x20, 0x40, 0x00, 0x00,
  //three
  0x00, 0x50, 0x10, 0x20, 0x10, 0x90, 0x00, 0x00,
  //four
  0x00, 0x30, 0x30, 0x50, 0xF8, 0x10, 0x00, 0x00,
  //five
  0x00, 0x40, 0x40, 0x50, 0x08, 0x50, 0x20, 0x00,
  //six
  0x00, 0x60, 0x40, 0x50, 0x00, 0x50, 0x20, 0x00,
  //seven
  0x00, 0x00, 0x10, 0x00, 0x20, 0x00, 0x00, 0x00,
  //eight
  0x00, 0x50, 0x40, 0x30, 0x40, 0x50, 0x20, 0x00,
  //nine
  0x00, 0x50, 0x00, 0x50, 0x30, 0x10, 0x00, 0x00,
  //colon
  0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00,
  //semicolon
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x20,
  //less
  0x00, 0x00, 0x10, 0x60, 0x60, 0x00, 0x00, 0x00,
  //equal
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
  //greater
  0x00, 0x00, 0x40, 0x30, 0x30, 0x00, 0x00, 0x00,
  //question
  0x00, 0x50, 0x10, 0x10, 0x20, 0x00, 0x00, 0x00,
  //at
  0x00, 0x40, 0x98, 0xC8, 0xC0, 0x00, 0x00, 0x00,
  //UPPER_A
  0x00, 0x20, 0x00, 0x50, 0x70, 0x00, 0x00, 0x00,
  //UPPER_B
  0x00, 0x10, 0x00, 0x70, 0x08, 0x10, 0x00, 0x00,
  //UPPER_C
  0x00, 0x50, 0x80, 0x80, 0x80, 0x50, 0x20, 0x00,
  //UPPER_D
  0x00, 0x10, 0x08, 0x08, 0x08, 0x10, 0x00, 0x00,
  //UPPER_E
  0x00, 0x40, 0x40, 0x70, 0x40, 0x40, 0x00, 0x00,
  //UPPER_F
  0x00, 0x40, 0x40, 0x70, 0x40, 0x40, 0x00, 0x00,
  //UPPER_G
  0x00, 0x50, 0x80, 0x80, 0x88, 0x48, 0x20, 0x00,
  //UPPER_H
  0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00,
  //UPPER_I
  0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
  //UPPER_J
  0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x00,
  //UPPER_K
  0x00, 0x10, 0x20, 0x60, 0x50, 0x10, 0x00, 0x00,
  //UPPER_L
  0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
  //UPPER_M
  0x00, 0x58, 0x58, 0x28, 0x28, 0x08, 0x00, 0x00,
  //UPPER_N
  0x00, 0x40, 0x40, 0x20, 0x00, 0x10, 0x00, 0x00,
  //UPPER_O
  0x00, 0x50, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00,
  //UPPER_P
  0x00, 0x50, 0x48, 0x50, 0x40, 0x40, 0x00, 0x00,
  //UPPER_Q
  0x00, 0x50, 0x88, 0x88, 0x88, 0x50, 0x30, 0x00,
  //UPPER_R
  0x00, 0x50, 0x48, 0x70, 0x50, 0x50, 0x00, 0x00,
  //UPPER_S
  0x00, 0x50, 0x40, 0x70, 0x08, 0x48, 0x20, 0x00,
  //UPPER_T
  0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
  //UPPER_U
  0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x20, 0x00,
  //UPPER_V
  0x00, 0x00, 0x50, 0x50, 0x40, 0x20, 0x00, 0x00,
  //UPPER_W
  0x00, 0xA8, 0xA8, 0x00, 0x50, 0x50, 0x00, 0x00,
  //UPPER_X
  0x00, 0x50, 0x50, 0x20, 0x50, 0x50, 0x00, 0x00,
  //UPPER_Y
  0x00, 0x50, 0x50, 0x20, 0x20, 0x20, 0x00, 0x00,
  //UPPER_Z
  0x00, 0x10, 0x10, 0x20, 0x40, 0x40, 0x00, 0x00,
  //bracketleft
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
  //backslash
  0x00, 0x40, 0x00, 0x20, 0x20, 0x10, 0x10, 0x00,
  //bracketright
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
  //asciicircum
  0x00, 0x20, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00,
  //underscore
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
  //grave
  0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //a
  0x00, 0x00, 0x70, 0x10, 0x50, 0x50, 0x00, 0x00,
  //b
  0x00, 0x00, 0x70, 0x00, 0x00, 0x50, 0x20, 0x00,
  //c
  0x00, 0x00, 0x70, 0x00, 0x00, 0x50, 0x20, 0x00,
  //d
  0x10, 0x10, 0x70, 0x10, 0x10, 0x50, 0x20, 0x00,
  //e
  0x00, 0x00, 0x70, 0x00, 0x70, 0x40, 0x20, 0x00,
  //f
  0x38, 0x20, 0x70, 0x20, 0x20, 0x20, 0x00, 0x00,
  //g
  0x00, 0x00, 0x70, 0x10, 0x10, 0x50, 0x10, 0x70,
  //h
  0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
  //i
  0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x00, 0x00,
  //j
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x60,
  //k
  0x00, 0x40, 0x50, 0x60, 0x60, 0x50, 0x00, 0x00,
  //l
  0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
  //m
  0x00, 0x00, 0xF0, 0xA8, 0xA8, 0xA8, 0x00, 0x00,
  //n
  0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
  //o
  0x00, 0x00, 0x70, 0x00, 0x88, 0x50, 0x20, 0x00,
  //p
  0x00, 0x00, 0x70, 0x00, 0x00, 0x50, 0x00, 0x00,
  //q
  0x00, 0x00, 0x70, 0x10, 0x10, 0x50, 0x10, 0x10,
  //r
  0x00, 0x00, 0x70, 0x40, 0x40, 0x40, 0x00, 0x00,
  //s
  0x00, 0x00, 0x70, 0x40, 0x30, 0x40, 0x20, 0x00,
  //t
  0x00, 0x20, 0x70, 0x20, 0x20, 0x20, 0x00, 0x00,
  //u
  0x00, 0x00, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00,
  //v
  0x00, 0x00, 0x80, 0x50, 0x50, 0x20, 0x00, 0x00,
  //w
  0x00, 0x00, 0xA8, 0x88, 0x00, 0x50, 0x00, 0x00,
  //x
  0x00, 0x00, 0x50, 0x50, 0x20, 0x50, 0x00, 0x00,
  //y
  0x00, 0x00, 0x88, 0x50, 0x50, 0x20, 0x20, 0x40,
  //z
  0x00, 0x00, 0x70, 0x10, 0x20, 0x40, 0x00, 0x00,
  //braceleft
  0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10,
  //bar
  0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  //braceright
  0x40, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40,
  //asciitilde
  0x00, 0x00, 0x00, 0x48, 0xB0, 0x00, 0x00, 0x00,
  //Data: 1714851741
};

sFONT Font8 = {
  Font8_Table,
  5, /* Width */
  8, /* Height */
};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
