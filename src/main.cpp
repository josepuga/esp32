//By José Puga. 2024. Under GPL3 License.

#include <Arduino.h>
#include "test_ble.hpp"
#include "test_rgb.hpp"

void setup() {
    Serial.begin(9600);
}

void loop() {

    // RGB on-board led
    //test_brightness();
    //test_7rgb_colors();

    // Bluetooth BLE
    test_debug_ble();
    //test_proximity_ble();  // uses RGB on-board Led
}
