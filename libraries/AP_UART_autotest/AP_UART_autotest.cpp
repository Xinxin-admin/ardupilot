#include "AP_UART_autotest.h"

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_Math/AP_Math.h>
#include <AP_BoardConfig/AP_BoardConfig.h>
#include <climits>

extern const AP_HAL::HAL &hal;

AP_UART_autotest *AP_UART_autotest::_singleton;

// constructor
AP_UART_autotest::AP_UART_autotest()
{
    if (_singleton != nullptr) {
        AP_HAL::panic("AP_UART_autotest must be singleton");
    }
    _singleton = this;
}

/// Startup initialisation.
void AP_UART_autotest::init(const AP_SerialManager& serial_manager)
{
    for (uint8_t i = 0; i < 6; i++) {
        _port[i] = nullptr;
        _port[i] = serial_manager.find_serial(AP_SerialManager::SerialProtocol_AUTO_TEST, i);
        if(_port[i] != nullptr) {
            _port[i]->begin(57600);
            _port[i]->set_flow_control(AP_HAL::UARTDriver::FLOW_CONTROL_DISABLE);
        }
    }
}

/*
  update all GPS instances
 */
void AP_UART_autotest::update(void) {
    int16_t tmp_data = 0;
    uint32_t data_num = 0;
    uint32_t i = 0;
    uint32_t j = 0;
    for (i = 0; i < 6; i++) {
        if (_port[i] != nullptr) {
            data_num = _port[i]->available();
            for (j = 0; j < data_num; j++) {
                tmp_data = _port[i]->read();
                _port[i]->write((uint8_t)(tmp_data + 1));
            }
        }
    }
}

namespace AP {

AP_UART_autotest &uart_autotest()
{
    return *AP_UART_autotest::get_singleton();
}

};
