/*
  LEDs.h - WS2812B control
  
  Licensed under whatever terms are required by GRBLESP
*/

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel leds(1, GPIO_NUM_13, NEO_GRB + NEO_KHZ800);

void leds_green(){
  leds.begin();
  leds.setPixelColor(0, leds.Color(0,127,0));  
  leds.show();
  leds.setBrightness(50);
}

void leds_orange(){
  leds.begin();
  leds.setPixelColor(0, leds.Color(255,165,0));  
  leds.show();
  leds.setBrightness(50);
}

void leds_red(){
  leds.begin();
  leds.setPixelColor(0, leds.Color(127,0,0));  
  leds.show();
  leds.setBrightness(50);
}

void leds_white(){
  leds.begin();
  leds.setPixelColor(0, leds.Color(127,127,127));  
  leds.show();
  leds.setBrightness(50);
}

void init_leds(){
  leds_red();
  delay(250);
  leds_orange();
  delay(250);
  leds_green();
  delay(250);
  leds_white();
}