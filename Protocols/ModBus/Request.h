#pragma once
#include "common.h"

namespace modbus {

class Request {
public:
    Request();
    ~Request();

    int GetSlaveAddress();
    int GetFunction();
    int GetStartingAddressHi();
    int GetStartingAddressLow();
    int GetQuantityHi();
    int GetQuantityLow();
    int GetErrorCheckHi();
    int GetErrorCheckLow();
    int GetErrorCheckLrc();
    int GetTrailer();
    void SetSlaveAddress(const byte* address);
    void SetFunction(const byte* function);
    void SetStartingAddressHi(const byte* startingAddressHi);
    void SetStartingAddressLow(const byte* startingAddressLow);
    void SetQuantityHi(const byte* quantityHi);
    void SetQuantityLow(const byte* quantityLow);
    void SetErrorCheckHi(const byte* errorCheckHi);
    void SetErrorCheckLow(const byte* errorCheckLow);
    void SetErrorCheckLrc(const byte* errorCheckLrc);
    void SetTrailer(const byte* trailer);

protected:
private:
    struct RtuFields {
        byte slaveAddress;
        byte function;
        byte startingAddressHi;
        byte startingAddressLow;
        byte quantityHi;
        byte quantityLow;
        byte errorCheckHi;
        byte errorCheckLow;
        byte trailer;
    };

    struct AsciiFields {
        byte header;
        byte slaveAddress[2];
        byte function[2];
        byte startingAddressHi[2];
        byte startingAddressLow[2];
        byte quantityHi[2];
        byte quantityLow[2];
        byte lrc[2];
        byte trailer[2];
    };

    ModbusCommandMode _mode;
    RtuFields _rtuFields_;
    AsciiFields _asciiFields_;
};

} // modbus