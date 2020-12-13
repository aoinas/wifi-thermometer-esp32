#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "WiFi.h"
#include "ThingSpeak.h"
#include "DHT.h"

#include "owmHelper.h"
#include "config.h"
#include "displayHelper.h"

// Temp & moisture sensor
#define DHTPIN 16
#define DHTTYPE DHT22

#define WIFI_TIMEOUT_MS 20000
#define DEEP_SLEEP_TIME_MIN 1

// OLED Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


WiFiClient client;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
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

  Wire.begin(5, 4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  dht.begin();

  showSplashScreen(display);
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

bool inverted = true;

void loop() {
  float h = dht.readHumidity();
// Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  showMainScreen(display, t, h);
  delay(5000);
  display.invertDisplay(inverted);
  
  inverted = !inverted;
}