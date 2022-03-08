#pragma once

#include "IODevice/SerialDevice.h"

class CommunicationManager {

public:
    CommunicationManager();
    ~CommunicationManager();

    ssize_t sendDataToDevice();
    ssize_t readDataFromDevice();

private:
    char* m_inputBuffer = new char[255];
    char* m_outputBuffer = new char[255];
};
