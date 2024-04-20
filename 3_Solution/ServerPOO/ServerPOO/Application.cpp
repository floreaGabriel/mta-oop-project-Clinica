#define _CRT_SECURE_NO_WARNINGS
#include "Application.h"
#include <string.h>
#include <iostream>

Application* Application::m_appInstance = nullptr;

Application& Application::getInstance()
{
	if (m_appInstance == nullptr)
		m_appInstance = new Application();
    m_appInstance->m_server = new ServerConnection(12345);
	return *m_appInstance;
}

bool Application::manageData(char* data)
{
    // de facut o clasa de utils care va avea functiile de gestionare a stringurilor, datelor ..

    char metaByte;
    metaByte = data[0];
    strcpy(data, data + 1);

    switch (metaByte)
    {
    case '1':
        manageLoginWindow(data);
    default:
        break;
    }

    return false;
}

bool Application::manageLoginWindow(const char* data)
{
    std::string bufferData(data);
    std::cout << bufferData;
    return true;
}

Application:: ~Application()
{
    if (m_appInstance == nullptr)
        return;
    if (m_appInstance->m_server != nullptr)
    {
        delete m_appInstance->m_server;
        m_appInstance->m_server = nullptr;
    }
    delete m_appInstance;
}
