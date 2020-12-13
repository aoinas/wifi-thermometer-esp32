#include "WiFi.h"

class OwmHelper {

public:
    OwmHelper(WiFiClient & wifiClient) {
        client = &wifiClient;
    }

private:
    WiFiClient * client;    



};