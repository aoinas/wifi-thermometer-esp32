#include "thingspeak_publisher.h"

#include <Arduino.h>
#include <cmath>
#include <esp_timer.h>

#include "ThingSpeak.h"

namespace wifi_thermometer
{

void ThingSpeakPublisher::OnNewMeasurement(const Measurement& measurement)
{
    measurements_.push_back(measurement);

    // Check whether is time to upload measurements to ThingSpeak
    int64_t timeSinceLastUpload = esp_timer_get_time() - previous_upload_time_;

    Serial.print("Time since last update: ");
    Serial.print( round(timeSinceLastUpload/1000000/60) );
    Serial.println(" minutes ");

    if ( timeSinceLastUpload > (PUBLISH_TO_WEB_DELAY * 60 * 1000000))
    {
        previous_upload_time_ = esp_timer_get_time();
        Upload();
    }
}

void ThingSpeakPublisher::Upload()
{
    bool connected = wifi_manager_.ConnectToWifi();

    if ( connected && WiFi.isConnected() )
    {
        Serial.println("Sending data to ThingSpeak...");
        Serial.print("esp_timer_get_time(): ");
        Serial.println( (int)esp_timer_get_time() );
        ThingSpeak.begin(wifi_manager_.GetWifiClient());

        auto avgInsideMeasurement = GetAverageMeasurement();

        ThingSpeak.setField(1, WiFi.RSSI());
        ThingSpeak.setField(2, avgInsideMeasurement.temperature_); // Inside temp
        ThingSpeak.setField(3, avgInsideMeasurement.humidity_); // Inside humid
        ThingSpeak.setField(4, 0); // Outside temp
        ThingSpeak.setField(5, 0); // Outside humid
        ThingSpeak.setField(6, 0); // Battery level
        ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
    }
    else
        Serial.println("Not connected to WiFi. Unable to send data to ThingSpeak");
}

float roundToNDecimals(const float& input, const int& decimalPlaces)
{
    float decimalPlaceFactor = pow(10.0f, decimalPlaces);
    float value = (int)(input * decimalPlaceFactor + .5); 
    float output = (float)value / decimalPlaceFactor; 

    return output;
}

Measurement ThingSpeakPublisher::GetAverageMeasurement()
{
    float avg_t = 0.0f;
    float avg_h = 0.0f;

    for (auto m : measurements_ )
    {
        avg_t += m.temperature_;
        avg_h += m.humidity_;
    }

    auto result = Measurement(  roundToNDecimals(avg_t/measurements_.size(), 1),
                                roundToNDecimals(avg_h/measurements_.size(), 1) );
    measurements_.clear();

    return result;
}


}