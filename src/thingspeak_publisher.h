#pragma once

#include <vector>

#include "measurement_observer_interface.h"
#include "measurement.h"
#include "wifi_manager.h"
//#include "owmHelper.h"

namespace wifi_thermometer
{

class ThingSpeakPublisher : public MeasurementObserverInterface
{
    public:
    ThingSpeakPublisher() : wifi_manager_(), previous_upload_time_(0) {}

    void OnNewMeasurement(const Measurement& measurement) override;
    void Upload();

    private:
    Measurement GetAverageMeasurement();

    WifiManager wifi_manager_;
    std::vector<Measurement> measurements_; // Stores measurements that happen between uploads
    unsigned long previous_upload_time_;
    //OwmHelper owm(m_WifiManager.getWifiClient());
};

} // namespace wifi_thermometer