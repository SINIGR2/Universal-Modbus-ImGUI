#pragma once

#include "IDevice.h"
#include "PComm.h"
#include "common.h"
#include <cstdint>

enum PortErrorCode {
    OK = SIO_OK,
    BADPORT = SIO_BADPORT,
    OUTCONTROL = SIO_OUTCONTROL,
    NODATA = SIO_NODATA,
    OPENFAIL = SIO_OPENFAIL,
    RTS_BY_HW = SIO_RTS_BY_HW,
    BADPARM = SIO_BADPARM,
    WIN32FAIL = SIO_WIN32FAIL,
    BOARDNOTSUPPORT = SIO_BOARDNOTSUPPORT,
    FAIL = SIO_FAIL,
    ABORTWRITE = SIO_ABORTWRITE,
    WRITETIMEOUT = SIO_WRITETIMEOUT
};

class SerialDevice : public IDevice {
public:
    using Port = int;
    using BaudRate = int;

    ~SerialDevice();
    SerialDevice(const SerialDevice&) = delete;
    SerialDevice(SerialDevice&&) = delete;
    SerialDevice& operator=(const SerialDevice&) = delete;
    SerialDevice& operator=(SerialDevice&&) = delete;

    static SerialDevice&
    instance()
    {
        static SerialDevice device;
        return device;
    };

    void open() override;
    void close() override;
    bool isOpen() const override;
    ssize_t read(char byte) override;
    ssize_t read(char* buffer, size_t size) override;
    ssize_t write(char byte) override;
    ssize_t write(char* buffer, size_t size) override;

    ssize_t setCommunicationParams();

    Port getPortNumber() const;
    BaudRate getPortBaudRate() const;

private:
    SerialDevice();
    void printErrorMessage(PortErrorCode code);

    Port m_port;
    BaudRate m_baudRate;
};
