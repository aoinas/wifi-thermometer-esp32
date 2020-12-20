#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "displayHelper.h"

// OLED Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

class DisplayManager
{
    public:
    DisplayManager() : m_Display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
    {

    }

    bool Begin()
    {
        Wire.begin(5, 4);
        if(!m_Display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) { 
            Serial.println(F("SSD1306 allocation failed"));
            return false;
        }

        showSplashScreen(m_Display);
        return true;
    }

    void OnNewMeasurement(const float& temperature, const float& humidity)
    {
        showMainScreen(m_Display, temperature, humidity);
    }

    Adafruit_SSD1306& getDisplay()
    {
        return m_Display;
    }

    private:

    Adafruit_SSD1306 m_Display;

};
