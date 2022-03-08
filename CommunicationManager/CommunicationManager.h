#pragma once

#include "IODevice/SerialDevice.h"

class CommunicationManager {

public:
    CommunicationManager();
    ~CommunicationManager();

    void sendDataToDevice();
    ssize_t  readDataFromDevice();

private:
    SerialDevice* m_pDevice;
    char m_inputBuffer[256];
    char m_outputBuffer[256];
};
