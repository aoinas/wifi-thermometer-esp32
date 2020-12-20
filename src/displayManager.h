#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "displayHelper.h"
#include "measurement_observer_interface.h"

// OLED Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

class DisplayManager : public MeasurementObserverInterface
{
    public:
    DisplayManager() : display_(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
    {

    }

    bool Begin()
    {
        Wire.begin(5, 4);
        if(!display_.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) { 
            Serial.println(F("SSD1306 allocation failed"));
            return false;
        }

        showSplashScreen(display_);
        return true;
    }

    void OnNewMeasurement(const float& temperature, const float& humidity) override
    {
        showMainScreen(display_, temperature, humidity);
    }

    Adafruit_SSD1306& getDisplay()
    {
        return display_;
    }

    private:

    Adafruit_SSD1306 display_;

};
