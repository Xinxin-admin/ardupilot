#include "AP_AdcAutoTest.h"
#include <AP_HAL/AP_HAL.h>
#include <AP_Vehicle/AP_Vehicle_Type.h>

extern const AP_HAL::HAL& hal;

AP_AdcAutoTest *AP_AdcAutoTest::_singleton;

const AP_Param::GroupInfo AP_AdcAutoTest::var_info[] = {
    AP_GROUPINFO("1_PIN", 0, AP_AdcAutoTest, _ADC1_pin, 0),
    AP_GROUPINFO("2_PIN", 1, AP_AdcAutoTest, _ADC2_pin, 1),
    AP_GROUPEND
};

AP_AdcAutoTest::AP_AdcAutoTest()
{
    AP_Param::setup_object_defaults(this, var_info);

    if (_singleton != nullptr) {
        AP_HAL::panic("AP_AdcAutoTest must be singleton");
    }
    _singleton = this;

}

// init - instantiate the battery monitors
void
AP_AdcAutoTest::init()
{
    if (_ADC1_pin == 100) {  // 说明此款飞控没有ADC1
        _adc1 = nullptr;
    } else {
        _adc1 = hal.analogin->channel(_ADC1_pin);
    }

    if (_ADC2_pin == 100) {  // 说明此款飞控没有ADC2
        _adc2 = nullptr;
    } else {
        _adc2 = hal.analogin->channel(_ADC2_pin);
    }
}

float AP_AdcAutoTest::read_ADC1() {
    if(_adc1 == nullptr)
        return 255.0f;

    // this copes with changing the pin at runtime
    _adc1->set_pin(_ADC1_pin);
    // get voltage
    return _adc1->voltage_average();
}

float AP_AdcAutoTest::read_ADC2() {
    if(_adc2 == nullptr)
        return 255.0f;

    // this copes with changing the pin at runtime
    _adc2->set_pin(_ADC2_pin);
    // get voltage
    return _adc2->voltage_average();
}

namespace AP {

AP_AdcAutoTest &adc_auto_test()
{
    return *AP_AdcAutoTest::get_singleton();
}

};
