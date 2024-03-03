//By José Puga. 2024. Under GPL3 License.

#include "test_rgb.hpp"
#include "onboardrgb7.hpp"


// Test brightness levels (0-255)
// Testear niveles de brillo (0-255)
void test_brightness() {
    constexpr int step {5};
    constexpr int min {0};
    constexpr int max {255};
    constexpr int pause {50};

    OnboardRgb7 rgb;
    // IMPORTANT!:
    // BY DEFAULT THE GPIO IS RGB_BUILTIN, but you can change it with...
    // POR DEFECTO EL GPIO ES RGB_BUILTIN, pero puedes cambiarlo con...
    // rgb.setGpio(your_gio_number);
loop:
    for (auto color : { color::red, color::green, color::blue, color::cyan, 
            color::purple, color::yellow, color::white}) {
        
        // From less to more...
        // De menos a más...
        for (auto brightness {min}; brightness <= max; brightness += step) {
            rgb.setBrightness(brightness);
            rgb.setColor(color);
            delay(pause);
        }

        // From more to less...
        // De más a menos...
        for (auto brightness {max}; brightness >= min; brightness -= step) {
            rgb.setBrightness(brightness);
            rgb.setColor(color);
            delay(pause);
        }
    }
    goto loop;
}

// Test all available colors (black = off)
// Testear todos los colores disponibles (black = apagado)
void test_7rgb_colors() {
    constexpr int brightness {16}; // 0 - 255
    constexpr int pause {1500};

    OnboardRgb7 rgb;
    rgb.setBrightness(brightness);
loop:
    for (auto color : { 
            color::red, color::green, color::blue, color::cyan, color::purple, 
            color::yellow, color::white, color::black}) {
        rgb.setColor(color);
        delay(pause);
    }
    goto loop;
}