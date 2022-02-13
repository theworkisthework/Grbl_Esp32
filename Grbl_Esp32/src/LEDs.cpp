/*
  LEDs.h - WS2812B control
  
  Licensed under whatever terms are required by GRBLESP
*/

#include <Adafruit_NeoPixel.h>

void init_leds(){
  Adafruit_NeoPixel leds(1, GPIO_NUM_13, NEO_GRB + NEO_KHZ800);
  leds.begin();
  leds.setPixelColor(0, leds.Color(127,127,127));  
  leds.show();
  leds.setBrightness(50);
}