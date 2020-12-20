#pragma once

class MeasurementObserverInterface
{
    public:
    virtual void OnNewMeasurement(const float& temperature, const float& humidity) = 0;
};