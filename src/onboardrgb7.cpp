//By José Puga. 2024. Under GPL3 License.

#include "onboardrgb7.hpp"

void OnboardRgb7::setGpio(uint8_t gpio) {
    gpio_num = gpio;
}

void OnboardRgb7::setColor(const RgbOnBoardColor& color) {
    current_color = color;
    neopixelWrite(gpio_num,
        current_color.r ? current_brightness: 0,
        current_color.g ? current_brightness: 0,
        current_color.b ? current_brightness: 0
    );
}
/*
void OnboardRgb7::setBrightness(float brightness) {

    if (brightness < 0.0f) {
        brightness = 0.0f;
    } else if (brightness > 1.0f) {
        brightness = 1.0f;
    }
    percent_brightness = brightness;
    current_brightness = percent_brightness * 255;
}
*/
void OnboardRgb7::setBrightness(uint8_t brightness) {
    current_brightness = brightness;
    // Why crashes?
    //FIXME: setColor(current_color);
}
/*
void OnboardRgb7::incBrightness(float step) {
    setBrightness(percent_brightness + step);
}
*/
