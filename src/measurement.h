#pragma once

class Measurement
{
    public:
    Measurement(const float& temperature, const float& humidity)
    {
        temperature_ = temperature;
        humidity_ = humidity;
    }
    float temperature_;
    float humidity_;
    // timestamp // where to get? 
};