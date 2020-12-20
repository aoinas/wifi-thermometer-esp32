#pragma once

#include "measurement.h"

class MeasurementObserverInterface
{
    public:
    virtual void OnNewMeasurement(const Measurement& measurement) = 0;
};