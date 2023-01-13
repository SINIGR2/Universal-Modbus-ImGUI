#pragma once

#include "common.h"

namespace modbus {

class ModBus {

public:
    ModBus();
    ~ModBus();

    void SetMode();
    ModbusCommandMode GetMode();

protected:
private:
    ModbusCommandMode _mode;
};

} // modbus