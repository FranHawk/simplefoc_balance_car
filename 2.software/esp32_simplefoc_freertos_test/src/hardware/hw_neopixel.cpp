#include "hw_neopixel.h"

#define LED1_PIN 16
#define LED2_PIN 17

#define LED_COUNT 24
#define LED_BRIGHTNESS 10

uint32_t neopixel_count = 0;

Neopixel_handler strip_1_handler{
    strip : Adafruit_NeoPixel(LED_COUNT, LED1_PIN, NEO_GRB + NEO_KHZ800),
    last_neopixel_count : 0,
    i : 0,
    state : 0
};
Neopixel_handler strip_2_handler{
    strip : Adafruit_NeoPixel(LED_COUNT, LED2_PIN, NEO_GRB + NEO_KHZ800),
    last_neopixel_count : 0,
    i : 0,
    state : 0
};

void hw_neopixel_init(void)
{

    strip_1_handler.strip.begin();
    strip_1_handler.strip.show();
    strip_1_handler.strip.setBrightness(LED_BRIGHTNESS);

    strip_2_handler.strip.begin();
    strip_2_handler.strip.show();
    strip_2_handler.strip.setBrightness(LED_BRIGHTNESS);
}

void neopixel_state_clear(Neopixel_handler &strip_handler)
{
    strip_handler.strip.setBrightness(LED_BRIGHTNESS);
    strip_handler.i = 0;
    strip_handler.state = 0;
    strip_handler.last_neopixel_count = neopixel_count;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip_1_handler.strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip_1_handler.strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip_1_handler.strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void neopixel_rainbow(Neopixel_handler &strip_handler)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
        strip_handler.strip.setPixelColor(i, Wheel((i + neopixel_count % 255) & 255));
    }
    strip_handler.strip.show();
}

void neopixel_fade_in_out(Neopixel_handler &strip_handler, uint8_t r, uint8_t g, uint8_t b, uint8_t fade_in_delay, uint8_t fade_out_delay, uint8_t brightness)
{
    if (strip_handler.state == 0 && (neopixel_count - strip_handler.last_neopixel_count > fade_in_delay))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        if (strip_handler.i < brightness)
        {
            for (uint8_t j = 0; j < LED_COUNT; j++)
            {
                strip_handler.strip.setPixelColor(j, r, g, b);
            }
            strip_handler.strip.setBrightness(strip_handler.i);
            strip_handler.strip.show();
            strip_handler.i++;
        }
        else
        {
            strip_handler.state = 1;
        }
    }
    else if (strip_handler.state == 1 && (neopixel_count - strip_handler.last_neopixel_count > fade_out_delay))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        if (strip_handler.i > 0)
        {
            for (int8_t j = 0; j < LED_COUNT; j++)
            {
                strip_handler.strip.setPixelColor(j, r, g, b);
            }
            strip_handler.strip.setBrightness(strip_handler.i);
            strip_handler.strip.show();
            strip_handler.i--;
        }
        else
        {
            strip_handler.state = 0;
        }
    }
    else if (strip_handler.state > 1)
    {
        strip_handler.state = 0;
    }
}

void neopixel_bounce(Neopixel_handler &strip_handler, uint8_t r, uint8_t g, uint8_t b, uint8_t eye_size, uint8_t speed_delay, uint8_t return_delay)
{
    if ((neopixel_count - strip_handler.last_neopixel_count > speed_delay) && strip_handler.state == 0)
    {
        strip_handler.last_neopixel_count = neopixel_count;
        if (strip_handler.i < LED_COUNT - eye_size - 2)
        {
            strip_handler.strip.clear();
            strip_handler.strip.setPixelColor(strip_handler.i, r / 4, g / 4, b / 4);
            for (int8_t j = 1; j <= eye_size; j++)
            {
                strip_handler.strip.setPixelColor(strip_handler.i + j, r, g, b);
            }
            strip_handler.strip.setPixelColor(strip_handler.i + eye_size + 1, r / 4, g / 4, b / 4);
            strip_handler.strip.show();
            strip_handler.i++;
        }
        else
        {
            strip_handler.state = 1;
        }
    }
    else if (strip_handler.state == 1)
    {
        if (neopixel_count - strip_handler.last_neopixel_count > return_delay)
        {
            strip_handler.last_neopixel_count = neopixel_count;
            strip_handler.i = LED_COUNT - eye_size - 2;
            strip_handler.state = 2;
        }
    }
    else if ((neopixel_count - strip_handler.last_neopixel_count > speed_delay) && strip_handler.state == 2)
    {
        strip_handler.last_neopixel_count = neopixel_count;
        if (strip_handler.i > 0)
        {
            strip_handler.strip.clear();
            strip_handler.strip.setPixelColor(strip_handler.i, r / 4, g / 4, b / 4);
            for (int8_t j = 1; j <= eye_size; j++)
            {
                strip_handler.strip.setPixelColor(strip_handler.i + j, r, g, b);
            }
            strip_handler.strip.setPixelColor(strip_handler.i + eye_size + 1, r / 4, g / 4, b / 4);
            strip_handler.strip.show();
            strip_handler.i--;
        }
        else
        {
            strip_handler.state = 3;
        }
    }
    else if (strip_handler.state == 3)
    {
        if (neopixel_count - strip_handler.last_neopixel_count > return_delay)
        {
            strip_handler.last_neopixel_count = neopixel_count;
            strip_handler.i = 0;
            strip_handler.state = 0;
        }
    }
    else if (strip_handler.state > 3)
    {
        strip_handler.state = 0;
    }
}

void neopixel_loop(Neopixel_handler &strip_handler, uint8_t r, uint8_t g, uint8_t b, uint8_t eye_size, uint8_t speed_delay)
{
    if ((neopixel_count - strip_handler.last_neopixel_count > speed_delay) && strip_handler.state == 0)
    {
        strip_handler.last_neopixel_count = neopixel_count;
        strip_handler.strip.clear();
        for (int8_t j = 1; j <= eye_size; j++)
        {
            strip_handler.strip.setPixelColor((strip_handler.i + j) % LED_COUNT, r, g, b);
        }
        strip_handler.strip.show();
        strip_handler.i++;
        if (strip_handler.i > LED_COUNT)
        {
            strip_handler.i = 0;
        }
    }
}

void neopixel_police_style_1(Neopixel_handler &strip_handler, uint8_t speed_delay, uint8_t return_delay)
{
    static uint32_t blue_color = strip_handler.strip.Color(0, 0, 255);
    static uint32_t red_color = strip_handler.strip.Color(255, 0, 0);

    if ((neopixel_count - strip_handler.last_neopixel_count > speed_delay) && ((strip_handler.state == 0) || (strip_handler.state == 2)))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        if (strip_handler.state == 0)
        {
            for (int8_t j = 0; j < LED_COUNT; j++)
            {
                if (j < (LED_COUNT / 2))
                {
                    strip_handler.strip.setPixelColor(j, blue_color);
                }
                else
                {
                    strip_handler.strip.setPixelColor(j, 0);
                }
            }
            strip_handler.strip.show();
            strip_handler.state = 1;
        }
        else
        {
            for (int8_t j = 0; j < LED_COUNT; j++)
            {
                if (j < (LED_COUNT / 2))
                {
                    strip_handler.strip.setPixelColor(j, 0);
                }
                else
                {
                    strip_handler.strip.setPixelColor(j, red_color);
                }
            }
            strip_handler.strip.show();
            strip_handler.state = 3;
        }
    }
    if ((neopixel_count - strip_handler.last_neopixel_count > return_delay) && ((strip_handler.state == 1) || (strip_handler.state == 3)))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        if (strip_handler.state == 1)
        {
            strip_handler.strip.clear();
            strip_handler.strip.show();
            strip_handler.state = 2;
        }
        else
        {
            strip_handler.strip.clear();
            strip_handler.strip.show();
            strip_handler.state = 0;
        }
    }
    if (strip_handler.state > 3)
    {
        strip_handler.state = 0;
    }
}

void neopixel_police_style_2(Neopixel_handler &strip_handler, uint8_t speed_delay, uint8_t return_delay)
{
    static uint32_t blue_color = strip_handler.strip.Color(0, 0, 255);
    static uint32_t red_color = strip_handler.strip.Color(255, 0, 0);

    if ((neopixel_count - strip_handler.last_neopixel_count > speed_delay) && (strip_handler.state == 0))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        for (int8_t j = 0; j < LED_COUNT; j++)
        {
            if (j < (LED_COUNT / 2))
            {
                strip_handler.strip.setPixelColor(j, blue_color);
            }
            else
            {
                strip_handler.strip.setPixelColor(j, red_color);
            }
        }
        strip_handler.strip.show();
        strip_handler.state = 1;
    }
    if ((neopixel_count - strip_handler.last_neopixel_count > return_delay) && (strip_handler.state == 1))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        strip_handler.strip.clear();
        strip_handler.strip.show();
        strip_handler.state = 0;
    }
    if (strip_handler.state > 1)
    {
        strip_handler.state = 0;
    }
}

void neopixel_spread_out(Neopixel_handler &strip_handler, uint32_t color_1, uint32_t color_2, uint8_t speed_delay, uint8_t return_delay)
{
    if ((neopixel_count - strip_handler.last_neopixel_count > speed_delay) && (strip_handler.state == 0))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        
        strip_handler.strip.setPixelColor(LED_COUNT / 2 -1 -strip_handler.i,color_1);
        strip_handler.strip.setPixelColor(LED_COUNT / 2+strip_handler.i,color_2);
        strip_handler.strip.show();

        strip_handler.i++;


        if(strip_handler.i>LED_COUNT / 2){
            strip_handler.state = 1;
            strip_handler.i = 0;
        } 
    }
    if ((neopixel_count - strip_handler.last_neopixel_count > return_delay) && (strip_handler.state == 1))
    {
        strip_handler.last_neopixel_count = neopixel_count;
        strip_handler.strip.clear();
        strip_handler.strip.show();
        strip_handler.state = 0;
    }
}