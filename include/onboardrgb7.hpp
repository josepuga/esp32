/*
    A wrapper class for Adafruit Neopixel to show RGB values in onboard ESP32 RGB Leds.
    It uses few colors. Enought for my personal use.

    Pros:
        - No external libraries required.
        - Easy to use.
    Cons:
        - Only 7 colors (+ black = off)

    If you need more colors, use FastLED library:
        https://lucidar.me/en/esp32/built-in-led-on-esp32-firebeetle-dfr0654/
*/
//By José Puga. 2024. Under GPL3 License.
#pragma once
#include <cstdint>
#include <Arduino.h>

// 
#ifndef RGB_BUILTIN
#error "RGB_BUILTIN was not defined. Does your board has onboard RGB led?"
//#define RGB_BUILTIN 8
#endif

struct RgbOnBoardColor {
    bool r {0};
    bool g {0};
    bool b {0};

    constexpr RgbOnBoardColor(bool red, bool green, bool blue) :
        r {red}, g {green}, b {blue} { }
};

// For future use, (no with NeoPixel)
// using ledcolor = uint32_t;

namespace color {
    constexpr RgbOnBoardColor red(true, false, false);
    constexpr RgbOnBoardColor green(false, true, false);
    constexpr RgbOnBoardColor blue(false, false, true);
    constexpr RgbOnBoardColor cyan(false, true, true);
    constexpr RgbOnBoardColor purple(true, false, true);
    constexpr RgbOnBoardColor yellow(true, true, false);
    constexpr RgbOnBoardColor white(true, true, true);
    constexpr RgbOnBoardColor black(false, false, false);
    /*
    constexpr ledcolor red {0xff0000};
    constexpr ledcolor green {0x00ff00};
    constexpr ledcolor blue {0x0000ff};
    constexpr ledcolor cyan {0x00ffff};
    constexpr ledcolor purple {0xff00ff};
    constexpr ledcolor yellow {0xffff00};
    constexpr ledcolor white {0xffffff};
    constexpr ledcolor black {0x000000};
    */
}

class OnboardRgb7 {
    public:
        void setGpio(uint8_t);
        void setColor(const RgbOnBoardColor&);
        void setBrightness(uint8_t);

    private:
        uint8_t gpio_num {RGB_BUILTIN};
        float percent_brightness {0.0f};
        uint8_t current_brightness {0};
        RgbOnBoardColor current_color{color::black};
};