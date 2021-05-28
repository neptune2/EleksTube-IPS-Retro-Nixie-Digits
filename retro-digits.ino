
// Proof-Of-Concept to display the retro digits extracted from Elektube IPS firware image
//
// Works on TTGO T-Display and Elekstube IPS Clock (with appropriate TFT_eSPI library User_Setup.h file for each)
// Portions of code adapted from https://github.com/SmittyHalibut/EleksTubeHAX/blob/main/old_code/SmittyHalibut-hacking-around/hello_world/hello_world.ino
//
// Thanks to SmittyHalibut, RedNax67 and frankcohen for their critical foundation work.
//
// Copyright (c) 2021 Neptune2. All rights reserved.
//
// This work is licensed under the terms of the MIT license.  
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the 
// Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

// Graphics and font library
#include <TFT_eSPI.h>  // Don't forget to configure User_Setup.h file

// Uncomment for TTGO-Display
// #define TTGO_T-DISPLAY

#include "retro.h"

TFT_eSPI tft = TFT_eSPI(135,240);  // Invoke TFT Display Library

#ifndef TTGO_T-DISPLAY
// Chip Select shift register
const uint8_t latchPin = 17;
const uint8_t clockPin = 16;
const uint8_t dataPin = 14;
#endif

const uint16_t* retro[] = { // nixie numbers pointers
  (uint16_t *) (retro_bin+9*(270*240)),
  (uint16_t *) (retro_bin+8*(270*240)),
  (uint16_t *) (retro_bin+7*(270*240)),
  (uint16_t *) (retro_bin+6*(270*240)),
  (uint16_t *) (retro_bin+5*(270*240)),
  (uint16_t *) (retro_bin+4*(270*240)),
  (uint16_t *) (retro_bin+3*(270*240)),
  (uint16_t *) (retro_bin+2*(270*240)),
  (uint16_t *) (retro_bin+1*(270*240)),
  (uint16_t *) retro_bin
  };
  
void setup()
{
#ifndef TTGO_T-DISPLAY
  digitalWrite(26, LOW);  // Reset the TFT Displays
  pinMode(26, OUTPUT);
  digitalWrite(26, HIGH);
  
  pinMode(27, OUTPUT); 
  digitalWrite(27, HIGH);  // Turn Displays on.

  // Setup 74HC595 chip select.
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00<<2);  // 0xDF selects left digit only, 0xFE selects right digit only, 0x00 selects all digits
  digitalWrite(latchPin, HIGH);
#endif

  tft.init();
  tft.setRotation(0); // Portrait orientation, USB at bottom for TTGO-display
  tft.setSwapBytes(true);  // Take care of endianess mismatch
  tft.fillScreen(TFT_BLACK); // Clear any residual display

#ifndef TTGO_T-DISPLAY
  pinMode(27, OUTPUT); 
  digitalWrite(27, HIGH);  // Turn Displays on
 #endif
}

void loop(){

  for(int i=0;i<10;i++){ // Loop through all the retro digits
   tft.pushImage(0, 0,  135, 240, retro[i]);
   delay(1000);
  }
}
