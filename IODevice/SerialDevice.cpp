#include "SerialDevice.h"
#include <iostream>
#include <vector>

static const std::vector<std::string> ErrorMessages = {
    "Ok.",
    "Port number is invalid. Check port number.",
    "The board is not the MOXA compatible intelligent board",
    "Not implemented",
    "No data to read.",
    "No such port or port is occupied by other program. Check com port configuration. Make sure no other program uses this com port.",
    "Can't control the port because it is set as auto H/W flow control by sio_flowctrl. Turn off hardware flow control first.",
    "Bad parameter. Check parameter.",
    "Calling Win32 function failed Call GetLastError to get the error code.",
    "The com port does not support this function.",
    "User abort blocked write.",
    "Write timeout."
};

SerialDevice::SerialDevice()
    : m_port(4)
    , m_baudRate(B38400)
{
}

SerialDevice::~SerialDevice()
{
    if (isOpen())
        close();
}

void
SerialDevice::open()
{
    auto result = sio_open(m_port);
    std::cerr << "Open port command. ";
    printErrorMessage(static_cast<PortErrorCode>(result));
}

void
SerialDevice::close()
{
    auto result = sio_close(m_port);
    std::cerr << "Close port command. ";
    printErrorMessage(static_cast<PortErrorCode>(result));
}

bool
SerialDevice::isOpen() const
{
    auto result = sio_open(m_port);
    if (result == 0)
        return false;

    return true;
}

ssize_t
SerialDevice::read(char byte)
{
    int ch = sio_getch(m_port);

    if (ch >= 0)
        byte = static_cast<char>(ch);

    return ch;
}

ssize_t
SerialDevice::read(char* buffer, size_t size)
{
    return sio_read(m_port, buffer, size);
}

ssize_t
SerialDevice::write(char byte)
{
    return sio_putch(m_port, byte);
}

ssize_t
SerialDevice::write(char* buffer, size_t size)
{
    return sio_write(m_port, buffer, size);
}

ssize_t
SerialDevice::setCommunicationParams(Port port, BaudRate baudRate)
{
    m_port = port;
    m_baudRate = baudRate;

    return sio_ioctl(m_port, m_baudRate, P_NONE | BIT_8 | STOP_1);
}

SerialDevice::Port
SerialDevice::getPortNumber() const
{
    return m_port;
}

SerialDevice::BaudRate
SerialDevice::getPortBaudRate() const
{
    return m_baudRate;
}

void
SerialDevice::printErrorMessage(PortErrorCode code)
{
    int messageIndex = std::abs(code);
    std::cerr << "Status: " << ErrorMessages.at(messageIndex) << std::endl;
}
