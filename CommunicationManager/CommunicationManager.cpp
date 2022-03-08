#include "CommunicationManager.h"

CommunicationManager::CommunicationManager()
{
    SerialDevice::instance().setCommunicationParams(4, B38400);
    SerialDevice::instance().open();

    for(int i = 0; i<255; ++i)
        m_inputBuffer[i] = 0;

    m_outputBuffer[0] = 0xFA;
    m_outputBuffer[1] = 0x03;
    m_outputBuffer[2] = 0x07;
    m_outputBuffer[3] = 0x00;
    m_outputBuffer[4] = 0x00;
    m_outputBuffer[5] = 0x24;
    m_outputBuffer[6] = 0x51;
    m_outputBuffer[7] = 0x2E;
}

CommunicationManager::~CommunicationManager()
{
    SerialDevice::instance().close();
}

ssize_t
CommunicationManager::sendDataToDevice()
{
    auto& instance = SerialDevice::instance();
    auto result = instance.write(m_outputBuffer, 8);
    return  result;
}

ssize_t
CommunicationManager::readDataFromDevice()
{
    return SerialDevice::instance().read(m_inputBuffer, 36);
}
