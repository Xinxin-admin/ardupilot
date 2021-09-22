#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_Math/AP_Math.h>
#include <AP_Param/AP_Param.h>

class AP_AdcAutoTest
{
public:
    AP_AdcAutoTest();

    /* Do not allow copies */
    AP_AdcAutoTest(const AP_AdcAutoTest &other) = delete;
    AP_AdcAutoTest &operator=(const AP_AdcAutoTest&) = delete;

    static AP_AdcAutoTest *get_singleton() {
        return _singleton;
    }

    static const struct AP_Param::GroupInfo var_info[];

    void init();

    float read_ADC1();
    float read_ADC2();

protected:

private:

    AP_Int8  _ADC1_pin;
    AP_Int8  _ADC2_pin;

    AP_HAL::AnalogSource *_adc1;
    AP_HAL::AnalogSource *_adc2;

    static AP_AdcAutoTest *_singleton;
};

namespace AP {
    AP_AdcAutoTest &adc_auto_test();
};
