#include "Request.h"
#include <string>

namespace modbus {

Request::Request()
    : _mode(NONE)
    , _rtuFields_({ 0, 0, 0, 0, 0, 0, 0, 0 })
    , _asciiFields_({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })
{
    _mode = NONE;
    _rtuFields_.slaveAddress = 20;
    _asciiFields_.slaveAddress[0] = '2';
    _asciiFields_.slaveAddress[1] = '0';
    _mode = ASCII;
}

int
Request::GetSlaveAddress()
{
    if (_mode == NONE)
        return _mode;

    if (_mode == RTU)
        return _rtuFields_.slaveAddress;

    return atoi(reinterpret_cast<char*>(_asciiFields_.slaveAddress));
}

int
Request::GetFunction()
{
    if (_mode == NONE)
        return _mode;

    if (_mode == RTU)
        return _rtuFields_.function;

    return atoi(reinterpret_cast<char*>(_asciiFields_.function));
}

int
Request::GetStartingAddressHi()
{
    if (_mode == NONE)
        return _mode;

    if (_mode == RTU)
        return _rtuFields_.startingAddressHi;

    return atoi(reinterpret_cast<char*>(_asciiFields_.startingAddressHi));
}

int
Request::GetStartingAddressLow()
{
    if (_mode == NONE)
        return _mode;

    if (_mode == RTU)
        return _rtuFields_.startingAddressLow;

    return atoi(reinterpret_cast<char*>(_asciiFields_.startingAddressLow));
}

int
Request::GetQuantityHi()
{
    if (_mode == NONE)
        return _mode;

    if (_mode == RTU)
        return _rtuFields_.quantityHi;

    return atoi(reinterpret_cast<char*>(_asciiFields_.quantityHi));
}

int
Request::GetQuantityLow()
{
    if (_mode == NONE)
        return _mode;

    if (_mode == RTU)
        return _rtuFields_.quantityLow;

    return atoi(reinterpret_cast<char*>(_asciiFields_.quantityLow));
}

int
Request::GetErrorCheckHi()
{
    if (_mode == NONE or _mode == ASCII)
        return NONE;

    return _rtuFields_.errorCheckHi;
}

int
Request::GetErrorCheckLow()
{
    if (_mode == NONE or _mode == ASCII)
        return NONE;

    return _rtuFields_.errorCheckLow;
}

int
Request::GetErrorCheckLrc()
{
    if (_mode == NONE or _mode == RTU)
        return NONE;

    return atoi(reinterpret_cast<char*>(_asciiFields_.lrc));
}

int
Request::GetTrailer()
{
    if (_mode == NONE or _mode == RTU)
        return _mode;

    return atoi(reinterpret_cast<char*>(_asciiFields_.trailer));
}

void
Request::SetSlaveAddress(const byte* slaveAddress)
{
    if (_mode == NONE)
        return;

    if (_mode == RTU)
        _rtuFields_.slaveAddress = *slaveAddress;
}

void
Request::SetFunction(const byte* function)
{
    if (_mode == NONE)
        return;

    if (_mode == RTU)
        _rtuFields_.function = *function;
}

void
Request::SetStartingAddressHi(const byte* startingAddressHi)
{
    if (_mode == NONE)
        return;

    if (_mode == RTU)
        _rtuFields_.startingAddressHi = *startingAddressHi;
}

void
Request::SetStartingAddressLow(const byte* startingAddressLow)
{
    if (_mode == NONE)
        return;

    if (_mode == RTU)
        _rtuFields_.startingAddressLow = *startingAddressLow;
}

void
Request::SetQuantityHi(const byte* quantityHi)
{
    if (_mode == NONE)
        return;

    if (_mode == RTU)
        _rtuFields_.quantityHi = *quantityHi;
}

void
Request::SetQuantityLow(const byte* quantityLow)
{
    if (_mode == NONE)
        return;

    if (_mode == RTU)
        _rtuFields_.quantityLow = *quantityLow;
}

void
Request::SetErrorCheckHi(const byte* errorCheckHi)
{
    if (_mode == NONE or _mode == ASCII)
        return;

    if (_mode == RTU)
        _rtuFields_.errorCheckHi = *errorCheckHi;
}

void
Request::SetErrorCheckLow(const byte* errorCheckLow)
{
    if (_mode == NONE or _mode == ASCII)
        return;

    if (_mode == RTU)
        _rtuFields_.errorCheckLow = *errorCheckLow;
}

void
Request::SetErrorCheckLrc(const byte* errorCheckLrc)
{
    if (_mode == NONE or _mode == RTU)
        return;
}

void
Request::SetTrailer(const byte* trailer)
{
    if (_mode == NONE or _mode == RTU)
        return;
}

} // modbus