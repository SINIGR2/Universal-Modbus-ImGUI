#include "CommunicationManager.h"

CommunicationManager::CommunicationManager()
{

}

CommunicationManager::~CommunicationManager()
{
    m_pDevice->close();
}
void
CommunicationManager::sendDataToDevice()
{
    m_pDevice->setCommunicationParams(4, B38400);
    m_pDevice->open();
    m_pDevice->write(m_outputBuffer, 8);
}
ssize_t
CommunicationManager::readDataFromDevice()
{
    return m_pDevice->read(m_inputBuffer, sizeof(m_inputBuffer));
}
