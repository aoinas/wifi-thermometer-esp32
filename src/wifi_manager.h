#pragma once

#include "WiFi.h"
#include "config.h"

#define WIFI_TIMEOUT_MS 20000

class WifiManager
{
    public:
    WifiManager()
    {

    }

    bool ConnectToWifi()
    {
        Serial.println("Connecting to WiFi");
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_NETWORK, WIFI_PASS);

        unsigned long startAttemptTime = millis();

        while ( WiFi.status() != WL_CONNECTED &&
                millis() - startAttemptTime < WIFI_TIMEOUT_MS )
            {
            Serial.print(".");
            delay(100);
            }

        if ( WiFi.status() != WL_CONNECTED )
        {
            Serial.print("failed");
            return false;
        }  
        else 
        {
            Serial.print("Connected ");
            Serial.println(WiFi.localIP());
            return true;
        }
    }

    WiFiClient& GetWifiClient()
    {
        return m_Client;
    }

    private:
    WiFiClient m_Client;

};