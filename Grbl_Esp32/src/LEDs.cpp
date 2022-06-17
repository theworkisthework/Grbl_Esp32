/*
  LEDs.h - WS2812B control

  Licensed under whatever terms are required by GRBLESP
*/
#include "Grbl.h"
#include <Adafruit_NeoPixel.h>

#ifdef ENABLE_LEDS

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// black, red, green blue, white - for my LEDs!
uint32_t primaryColourArray[] = { leds.Color(0,0,0), leds.Color(0,255,0), leds.Color(255,0,0), leds.Color(0,0,255), leds.Color(255,255,255) };

void leds_wheel(uint32_t index, uint8_t b) {
  leds.begin();
  leds.setBrightness(b);
  leds.setPixelColor(0, primaryColourArray[index]);
  leds.show();
}

void leds_green() {
  leds.begin();
  leds.setPixelColor(0, leds.Color(0,127,0));
  leds.show();
  leds.setBrightness(50);
}

void leds_orange() {
  leds.begin();
  leds.setPixelColor(0, leds.Color(255,165,0));
  leds.show();
  leds.setBrightness(50);
}

void leds_red() {
  leds.begin();
  leds.setPixelColor(0, leds.Color(127,0,0));
  leds.show();
  leds.setBrightness(50);
}

void leds_white() {
  leds.begin();
  leds.setPixelColor(0, leds.Color(127,127,127));
  leds.show();
  leds.setBrightness(50);
}

typedef struct {
    uint32_t colour_index;
    uint8_t brightness;
    uint32_t duration;
} pixel_control_t;

#define QUEUE_LEN             10  // TODO
xQueueHandle leds_neopixel_queue;    // used by neopixel LEDs


pixel_control_t test_pixel_controls[] = {
    {3, 250, 1000},
    {2, 250, 1000},
    {1, 250, 1000},
    {3, 150, 1000},
    {2, 150, 1000},
    {1, 150, 1000},
    {3, 5, 2500},
    {2, 5, 2500},
    {1, 5, 2500},
    {4, 5, 2500}
};

void send_test_sequence_to_queue() {
    for (uint32_t i = 0; i < sizeof(test_pixel_controls) / sizeof(pixel_control_t); i++) {
        xQueueSendFromISR(leds_neopixel_queue, &test_pixel_controls[i], NULL);
        char msg[64];
        snprintf(msg, 64, "add to queue index %d", i);
        grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, msg);
    }
}

// this is the neopixel LEDs task
void ledsNeopixelTask(void* pvParameters) {
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Fiddling with LEDs");
    for (uint32_t i = 0; i < 5; i++) {
      leds_wheel(i, (5-i) * 50);
      delay(500);
    }
    while (true) {
        char msg[64];
        pixel_control_t pixel_control;
        xQueueReceive(leds_neopixel_queue, &pixel_control, portMAX_DELAY);  // block until receive queue
        snprintf(msg, 64, "take off queue colour index %d %d %d", pixel_control.colour_index, pixel_control.brightness, pixel_control.duration);
        grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, msg);
        leds_wheel(pixel_control.colour_index, pixel_control.brightness);
        delay(pixel_control.duration);
    }
}

void leds_init() {
    // setup task used for neopixel LEDs
    leds_neopixel_queue = xQueueCreate(QUEUE_LEN, sizeof(pixel_control_t));
    xTaskCreate(ledsNeopixelTask,
                "ledsNeopixelTask",
                3096,
                NULL,
                5,  // priority
                NULL);
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Task Create ledsNeopixelTask");
    send_test_sequence_to_queue();
}

// TODO Do we need a Task?!
// TODO pass some data in..!
void IRAM_ATTR isr_leds_neopixel() {
    int evt;
    xQueueSendFromISR(leds_neopixel_queue, &evt, NULL);
}

#endif
