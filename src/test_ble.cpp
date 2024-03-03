//By José Puga. 2024. Under GPL3 License.

#include "test_ble.hpp"
#include "proximityble.hpp"
#include "onboardrgb7.hpp" // for test_proximity_ble()

#include <vector>

// Callback if a good mac is in range...
void good_mac_in_range(const std::string &mac, int signal);
// Callback if a bad mac is in range...
void bad_mac_in_range(const std::string &mac, int signal);
// Callback when the good or bad mac leaves range...
void mac_leaves_range(const std::string &mac);

uint8_t signal_to_brightness(int signal);

void test_proximity_ble() {
    using namespace std;
    ProximityBle pb; // min_signal_strength

    // Good MACS (access granted)
    // Buenas MACS (acceso permitido)
    vector<string> good_macs{
        "xx:02:ab:01:e1:20",
        "00:00:aa:bb:cc:dd",
        "ff:ff:22:44:66:88",
    };
    // Bad MACS (access denied)
    // Malas MACS (acceso denegado)
    vector<string> bad_macs{
        "13:02:ab:01:e1:20",
        "c5:00:00:c5:c5:c5",
        "ff:12:34:56:78:90",
    };

    // NOTE: 3st Parameter "callback on leave range" is OPTIONAL
    // NOTA: El 3er Parámetro "callback al dejar el rango" es OPCIONAL
    for (auto mac : good_macs)
    {
        pb.addCallbackForMac(mac, good_mac_in_range, mac_leaves_range);
    }
    for (auto mac : bad_macs)
    {
        pb.addCallbackForMac(mac, bad_mac_in_range, mac_leaves_range);
    }

    // Loop forever scanning and trigger the callback if a know mac is in range
    // Bucle infito escaneando y lanzando en callback si una mac conocida está en rango
    while (true)
    {
        pb.scan(); // Default 1 second, use: pb.scan(seconds)
    }
}

void good_mac_in_range(const std::string &mac, int signal)
{ // In this case we dont need to use mac variable.
    OnboardRgb7 rgb;
    auto brightness = signal_to_brightness(signal);
    rgb.setBrightness(brightness);
    rgb.setColor(color::green);
}

void bad_mac_in_range(const std::string &mac, int signal)
{ // In this case we dont need to use mac variable.
    OnboardRgb7 rgb;
    rgb.setBrightness(180);
    auto current_color{color::blue};
    if (signal >= -30)
    {
        current_color = color::red;
    }
    else if (signal >= -50)
    {
        current_color = color::yellow;
    }
    rgb.setColor(current_color);
}

// When a mac leaves the signal simply turn off the led
// Cuando una mac deja el rango, sencillamente apagamos el led
void mac_leaves_range(const std::string &mac)
{ // In this case we dont need to use mac variable.
    OnboardRgb7 rgb;
    rgb.setColor(color::black);
}

uint8_t signal_to_brightness(int signal)
{
    constexpr int min_signal = MIN_SIGNAL_STRENGTH;
    constexpr int max_signal = -1;

    int brightness = static_cast<int>((signal - min_signal) / static_cast<double>(max_signal - min_signal) * (255 - 1) + 0.5);


    // Range between 1 and 255
    brightness = std::max(1, std::min(brightness, static_cast<int>(255)));

    return static_cast<uint8_t>(brightness);
}


void test_debug_ble()
{
    ProximityBle pb;
    pb.setDebugMode(true);
    while (true)
    {
        Serial.println("-------------------------------------------------");
        pb.scan(); // Default 1 second, use: pb.scan(seconds)
    }
}

