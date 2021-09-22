#pragma once

#include <AP_HAL/AP_HAL.h>
#include <inttypes.h>
#include <AP_Common/AP_Common.h>
#include <AP_Common/Location.h>
#include <AP_Param/AP_Param.h>
#include <AP_SerialManager/AP_SerialManager.h>

/// @class AP_UART_autotest
/// GPS driver main class
class AP_UART_autotest
{
public:
    AP_UART_autotest();

    /* Do not allow copies */
    AP_UART_autotest(const AP_UART_autotest &other) = delete;
    AP_UART_autotest &operator=(const AP_UART_autotest&) = delete;

    static AP_UART_autotest *get_singleton() {
        return _singleton;
    }

    /// Startup initialisation.
    void init(const AP_SerialManager& serial_manager);

    /// Update GPS state based on possible bytes received from the module.
    /// This routine must be called periodically (typically at 10Hz or
    /// more) to process incoming data.
    void update(void);
 
protected:

private:
    static AP_UART_autotest *_singleton;

    AP_HAL::UARTDriver *_port[6];
};

namespace AP {
    AP_UART_autotest &uart_autotest();
};
