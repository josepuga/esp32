//By José Puga. 2024. Under GPL3 License.

#include "proximityble.hpp"
#include <utility>
#include <Arduino.h>  // For debug print only

//TODO: Check initalization errors!!!
ProximityBle::ProximityBle(int min_signal_strength) :
        min_signal_strength {min_signal_strength} {
    if (! initialized) {
        BLEDevice::init("");
        ble_scan = BLEDevice::getScan();
        ble_scan->setActiveScan(true);
        initialized = true;    
    }
}

void ProximityBle::scan(uint seconds) {
    using namespace std;

    std::map<string, int> data {};
    BLEScanResults results = ble_scan->start(seconds);
    BLEAdvertisedDevice device;
    for (auto i = 0; i < results.getCount(); i++) {
        device = results.getDevice(i);
        auto mac = device.getAddress().toString();
        auto rssi = device.getRSSI();
        //data.push_back( {mac, rssi});
        data.insert(make_pair(mac, rssi));
        if (debug_mode) {
            Serial.printf("MAC=%s RSSI=%d Name=%s\n",
                 mac.c_str(), rssi, device.getName().c_str());
        }
    }
    for (auto &cbi : callback_items) {
        string mac {cbi.first};
        int rssi {0};
        if (cbi.second.in) {                        // VALID callback in function?
            if (data.count(mac)) {                  // The MAC has been scanned?
                rssi = data.find(mac)->second; 
                cbi.second.in_range = true;         // Set it in-range
                cbi.second.in(mac, rssi);           // Callback in function
            } else {   // If no MAC, and WAS in-range call leave callback
                if (cbi.second.leave && cbi.second.in_range) {
                    cbi.second.in_range = false;    // Set it out of range
                    cbi.second.leave(mac);          // Callback leave function
                }
            }
        }
    }
}

void ProximityBle::addCallbackForMac(std::string mac, bt_callback_in callback_in, bt_callback_leave callback_leave) {
    callbacks cb; // {.in = callback_in, .leave = callback_leave};
    cb.in = callback_in;
    cb.leave = callback_leave;
    callback_items.insert({mac, std::move(cb)});        
}

void ProximityBle::setDebugMode(bool mode) {
    debug_mode = mode;
}