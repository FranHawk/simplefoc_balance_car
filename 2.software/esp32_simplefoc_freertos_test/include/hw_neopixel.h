#ifndef  __HW_NEOPIXEL_H
#define __HW_NEOPIXEL_H

#include <Adafruit_NeoPixel.h>

typedef struct Neopixel_handler_struct{
    Adafruit_NeoPixel strip;
    uint32_t last_neopixel_count;
    uint8_t i,state;
}Neopixel_handler;

extern Neopixel_handler strip_1_handler;
extern Neopixel_handler strip_2_handler;

extern uint32_t neopixel_count;

void hw_neopixel_init();

void neopixel_state_clear(Neopixel_handler &strip_handler);

void neopixel_rainbow(Neopixel_handler & strip_handler);

void neopixel_bounce(Neopixel_handler & strip_handler,uint8_t r, uint8_t g, uint8_t b, uint8_t eye_size, uint8_t speed_delay, uint8_t return_delay);

void neopixel_loop(Neopixel_handler & strip_handler,uint8_t r, uint8_t g, uint8_t b, uint8_t eye_size, uint8_t speed_delay);

void neopixel_fade_in_out(Neopixel_handler & strip_handler,uint8_t r, uint8_t g, uint8_t b,uint8_t fade_in_delay,uint8_t fade_out_delay,uint8_t brightness);

void neopixel_police_style_1(Neopixel_handler & strip_handler,uint8_t speed_delay,uint8_t return_delay);

void neopixel_police_style_2(Neopixel_handler & strip_handler,uint8_t speed_delay,uint8_t return_delay);

void neopixel_spread_out(Neopixel_handler &strip_handler, uint32_t color_1, uint32_t color_2, uint8_t speed_delay, uint8_t return_delay);

#endif 