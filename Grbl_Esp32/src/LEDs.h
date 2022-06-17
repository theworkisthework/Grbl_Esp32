/*
  LEDs.h - WS2812B control

  Licensed under whatever terms are required by GRBLESP
*/

void leds_init();
void leds_wheel(uint32_t index, uint8_t b);
void leds_white();
void leds_green();
void leds_orange();
void leds_red();
