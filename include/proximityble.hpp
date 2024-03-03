//By José Puga. 2024. Under GPL3 License.

#pragma once
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>

#include <string>
#include <map>

using bt_callback_in = void (*) (const std::string&, int);
using bt_callback_leave = void (*) (const std::string&);

constexpr int MIN_SIGNAL_STRENGTH {-70};

class ProximityBle {
    public:
        ProximityBle(int min_signal_strength = MIN_SIGNAL_STRENGTH);
        void addCallbackForMac(std::string, bt_callback_in, bt_callback_leave = nullptr);
        void scan(uint seconds = 1);
        void setDebugMode(bool);

    private:
        int min_signal_strength {0};
        // Must be static, because BLEDevice.
        inline static BLEScan *ble_scan;
        inline static bool initialized;
        bool debug_mode {false};

        struct callbacks {
            bt_callback_in in {nullptr};
            bt_callback_leave leave {nullptr};
            bool in_range {false};
        };
        std::map<std::string, ProximityBle::callbacks> callback_items;
};