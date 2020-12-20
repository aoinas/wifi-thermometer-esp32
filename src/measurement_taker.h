#pragma once

#include <vector>

#include "DHT.h"
#include "config.h"
#include "measurement_observer_interface.h"

#define DHTTYPE DHT22

class MeasurementTaker
{
    public:
    MeasurementTaker() : sensor_(DHTPIN, DHTTYPE) {}

    ~MeasurementTaker()
    {
        observers_.clear();
    }
    
    void Begin()
    {
        sensor_.begin();
    }

    void Subscribe(MeasurementObserverInterface* observer)
    {
        observers_.push_back(observer);
    }

    void Measure()
    {
        Measurement m(  sensor_.readTemperature(),
                        sensor_.readHumidity() );
        
        // Notify observers on new measurements
        for (auto observer : observers_)
        {
            observer->OnNewMeasurement(m);
        }
    }

    private:
    std::vector<MeasurementObserverInterface*> observers_;
    DHT sensor_;
};