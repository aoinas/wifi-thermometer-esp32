#include <Arduino.h>

#include "config.h"

#include "measurement_taker.h"
#include "thingspeak_publisher.h"

#ifdef USE_DISPLAY
#include "displayManager.h"
DisplayManager m_DisplayManager;
#endif

#define DEEP_SLEEP_TIME_MIN 1

using namespace wifi_thermometer;

MeasurementTaker measurement_taker;
ThingSpeakPublisher measurement_publisher;

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
  measurement_taker.Subscribe(&measurement_publisher);

  #ifdef USE_DISPLAY
  m_DisplayManager.Begin();
  measurement_taker.Subscribe(&m_DisplayManager);
  #endif
  
  delay(2000);

  //goToDeepSleep();
}

void loop() {
  
    measurement_taker.Measure();
    delay(10000);

}