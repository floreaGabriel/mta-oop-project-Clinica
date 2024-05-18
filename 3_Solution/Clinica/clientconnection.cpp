#include "ClientConnection.h"
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>

ClientConnection* ClientConnection::m_instance = nullptr;

ClientConnection& ClientConnection::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new ClientConnection();

    return *m_instance;
}

bool ClientConnection::connectToServer(const char * ip, int port)
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        return 1; // Indicate failure
    }

    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    inet_pton(AF_INET, ip, &serverAddr.sin_addr);

    if (connect(m_clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Connection failed\n";
        closesocket(m_clientSocket);
        return false;
    }

    std::cout<< "Connected to server!\n";
    return true;
}

bool ClientConnection::sendData(const char * buffer)
{
    int bufferLength = strlen(buffer);
    int bytesSent = send(m_clientSocket, buffer, bufferLength, 0);
    if (bytesSent == -1) {
        std::cerr << "Error: Send failed\n";
        return false;
    }
    return true;
}

bool ClientConnection::receiveData(char* buffer, int bufferSize) {
    int bytesRead = recv(m_clientSocket, buffer, bufferSize, 0);
    std::cout<<"Buffer:   "<<buffer;
    if (bytesRead == -1) {
        std::cerr << "Error: Receive failed\n";
        return false;
    }
    buffer[bytesRead] = '\0'; // Null-terminate the received data
    return true;
}

ClientConnection:: ~ClientConnection()
{
    closesocket(m_clientSocket);
}
