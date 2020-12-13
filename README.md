# wifi-thermometer-esp32

Software for WIFI thermometer.
Plan is to use this to monitor temperature and humidity in the garage, compare results to outside temperature (fetched from the internets) and send results to ThingSpeak, where historical data can be browsed.

## Parts used
- ESP32 with OLED display
- Temperature sensor DHT22

Still very much work-in-progress

## What is working
- Temperature and humidity is measured correctly
- Temp and humidity are shown in the screen

## What is NOT implemented/working
- Getting temperature and humidity values from internets
- Sending measurements to ThingSpeak

## Possible features in the future
- Battery operation with deep sleep

