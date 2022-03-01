#pragma once
#include <cstdint>
#include "common.h"

class IDevice {
public:
    virtual ~IDevice() {};
    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
    virtual ssize_t read(char byte) = 0;
    virtual ssize_t read(char* buffer, size_t size) = 0;
    virtual ssize_t write(char byte) = 0;
    virtual ssize_t write(char* buffer, size_t size) = 0;
};
