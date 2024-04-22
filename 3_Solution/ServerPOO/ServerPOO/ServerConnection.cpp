#include "ServerConnection.h"
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "Application.h"
#include "RequestRegNormalUser.h"
#include "DataBase.h"
//#include "BDComm.h"

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <thread>



void ServerConnection::start(int port)
{
	if (!createSocket(port))
	{
		return;
	}

	if (!bindSocket(port))
	{
		closesocket(serverSocket);
		return;
	}
	if (!listenForConnections())
	{
		closesocket(serverSocket);
		return;
	}
}

//int ServerConnection::receive(char* receive, const int size) const
//{
//	int receive_bytes = ::recv(serverSocket, receive, size, 0);
//	return receive_bytes;
//}

bool ServerConnection::createSocket(int port) {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	// Create a socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		std::cerr << "Error: Could not create socket\n";
		return false;
	}
	return true;
}

bool ServerConnection::bindSocket(int port)
{
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port); // Port number
	serverAddr.sin_addr.s_addr = INADDR_ANY; // Any incoming interface

	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		std::cerr << "Error: Bind failed\n";
		return false;
	}
	std::cout << "Server started and listening on port " << port << std::endl;
	return true;
}

bool ServerConnection::listenForConnections() {
	// Listen for incoming connections

	if (listen(serverSocket, SOMAXCONN) == -1) {
		std::cerr << "Error: Listen failed\n";
		return false;
	}
	std::cout << "Waiting for incoming connection...\n";
	// Accept incoming connections
	while (true) {
		std::cout << "ma aflu in listen for connections!in while\n";
		int clientSocket = accept(serverSocket, nullptr, nullptr);
		if (clientSocket == -1) {
			std::cerr << "Error: Accept failed\n";
			continue;
		} 


		std::cout << "Connection accepted from client!\n";
		// Create a new thread to handle the client
		std::thread clientThread(&ServerConnection::handleClient, this, clientSocket);
		clientThread.detach(); // Detach the thread so it runs independently
	}
	return true;
}

void ServerConnection::handleClient(int clientSocket) {
	// Handle client request
	char buffer[1024];

	while (true)
	{
		std::cout << "(Asteapta interactiune de la client...)\n";
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived == SOCKET_ERROR) {
			std::cerr << "Error: Receive failed\n";
		}
		else if (bytesReceived == 0) {
			std::cerr << "Client disconnected\n";
		}
		else {
			buffer[bytesReceived] = '\0'; // Null-terminate the received data



			if (DataBase::getInstance().connect())
			{
				printf("Conectat la baza de date!\n");
			}
			else
			{
				printf("Nu se poate realiza conexiunea cu baza de date!\n");
			}

			IRequest* request = IRequest::Factory::requestSelector(buffer);
			request->manage_request();

			DataBase::getInstance().disconnect();

			char* answear = request->manage_answear();

			memset(buffer, 0, sizeof(buffer));

			send(clientSocket, answear, strlen(answear), 0);

			printf("Raspuns trimis catre client: %s!\n", answear);
			//std::cout << "Received data from client: " << buffer << std::endl;
		}
	}
	

	// Close client socket
	closesocket(clientSocket);
}
