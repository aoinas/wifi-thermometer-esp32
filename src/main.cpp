#include <Arduino.h>

#include "WiFi.h"
#include "ThingSpeak.h"
#include "DHT.h"

#include "owmHelper.h"
#include "config.h"

#ifdef USE_DISPLAY
#include "displayManager.h"
DisplayManager m_DisplayManager;
#endif

// Temp & moisture sensor
#define DHTPIN 16
#define DHTTYPE DHT22

#define WIFI_TIMEOUT_MS 20000
#define DEEP_SLEEP_TIME_MIN 1

WiFiClient client;

OwmHelper owm(client);
DHT dht(DHTPIN, DHTTYPE);

void connectToWifi()
{
  Serial.print("Connecting to WiFi");
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
  }  
  else 
  {
    Serial.print("Connected ");
    Serial.println(WiFi.localIP());
  }
}

void goToDeepSleep()
{
  Serial.println("Going to sleep...");
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME_MIN * 60 * 1000000);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  #ifdef USE_DISPLAY
  m_DisplayManager.Begin();
  #endif

  dht.begin();

  
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
  
  float t = dht.readTemperature(); // In celsius
  float h = dht.readHumidity();

  #ifdef USE_DISPLAY
  m_DisplayManager.OnNewMeasurement(t, h);
  #endif

}