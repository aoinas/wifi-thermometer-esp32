#include <Arduino.h>

#include "ThingSpeak.h"

#include "owmHelper.h"
#include "config.h"
#include "wifi_manager.h"
#include "measurement_taker.h"


#ifdef USE_DISPLAY
#include "displayManager.h"
DisplayManager m_DisplayManager;
#endif

#define DEEP_SLEEP_TIME_MIN 1

WifiManager m_WifiManager;
OwmHelper owm(m_WifiManager.getWifiClient());
MeasurementTaker measurement_taker;

void goToDeepSleep()
{
  Serial.println("Going to sleep...");
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME_MIN * 60 * 1000000);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  measurement_taker.Begin();

  #ifdef USE_DISPLAY
  m_DisplayManager.Begin();
  measurement_taker.Subscribe(&m_DisplayManager);
  #endif

  
  delay(2000);



/*
  connectToWifi();

  if ( WiFi.isConnected() )
  {
    Serial.println("Sending data to ThingSpeak");
    ThingSpeak.begin(client);

    ThingSpeak.setField(1, WiFi.RSSI());
    ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
  }
  else
    Serial.println("Not connected to WiFi. Unable to send data to ThingSpeak");
    */
  
  //goToDeepSleep();
}

void loop() {
  
    measurement_taker.Measure();
    delay(10000);

}