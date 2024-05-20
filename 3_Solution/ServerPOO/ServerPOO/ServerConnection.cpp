#include "ServerConnection.h"
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "Application.h"
#include "RequestRegNormalUser.h"
#include "DataBase.h"
#include "Exception.h"
#include "CUtils.h"

//#include "BDComm.h"

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <thread>
#include <iomanip>
#include <fstream>
#include <sstream>



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




void ServerConnection::sendImages(int clientSocket, char * answear)
{
	// 6$nume#pret#caleaImagine$nume#pret....
	// 7#calea
	std::vector<std::string> split = CUtils::understandData(answear, '#');

	// parcurg fiecare cale pentru imagini
		std::ifstream file(split[1], std::ios::binary);


		if (file.is_open()) {
			// Trimite datele către client
			constexpr int bufferSize = 40960; // Dimensiunea buffer-ului pentru citirea din fișier
			std::vector<uint8_t> buffer(bufferSize);

			file.seekg(0, std::ios::end);

			int fileSize = file.tellg();
			std::string mesaj_dimensiune = "7#" + to_string(fileSize);
			send(clientSocket, mesaj_dimensiune.c_str(), mesaj_dimensiune.length(), 0);

			file.seekg(0, std::ios::beg);

			int bytesRemained = fileSize;
			int bytesSent = 0;
			int bytesThatHasBeenSent = 0;
			for (int i = 1; i <= (fileSize / 40960) + 1; i++)

			{
				char p[10];
				int brec = recv(clientSocket, p, sizeof(p), 0);
				p[brec] = '\0';
				if (strcmp(p, "ACCEPT") == 0)
				{

					if (bytesRemained < 40960)
					{
						//fread(buffer, 1, bytesRemained, file);
						file.read(reinterpret_cast<char*>(buffer.data()), bytesRemained);
						bytesSent = send(clientSocket, reinterpret_cast<char*>(buffer.data()), bytesRemained, 0);
						bytesThatHasBeenSent -= bytesSent;
					}
					else
					{
						file.read(reinterpret_cast<char*>(buffer.data()), 40960);
						//fread(buffer, 1, 40960, file);
						bytesSent = send(clientSocket, reinterpret_cast<char*>(buffer.data()), 40960, 0);
						bytesThatHasBeenSent -= bytesSent;
					}

					bytesRemained -= 40960;
					std::cout << bytesSent << std::endl;
					

				}

			}
			file.close();
		}
		else {
			std::cerr << "Error: Unable to open file for reading." << std::endl;
		}

	

	return;
}


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

	if (DataBase::getInstance().connect())
	{
		printf("Conectat la baza de date!\n");
	}
	else
	{
		throw Exception("Nu se poate conecta la baza de date!\n", 22);
	}

	while (true)
	{
		try {

			std::cout << " <------- Asteapta interactiune de la client ------->\n";
			int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (bytesReceived == SOCKET_ERROR) {
				throw Exception("Primirea datelor a esuat!\n", 20);
				break;
			}
			else if (bytesReceived == 0) {
				throw Exception("Client deconectat!\n", 21);
				break;
			}
			else {
				cout << "Datele s-au primit cu succes!\n";
				buffer[bytesReceived] = '\0'; // Null-terminate the received data



				

				IRequest* request = IRequest::Factory::requestSelector(buffer);
				request->manage_request();


				char* answear = request->manage_answear();
				memset(buffer, 0, sizeof(buffer)); // resetez bufferul in care am primit mesajul

				if (answear[0] == '7')
				{
					sendImages(clientSocket, answear);
					printf("Imagine trimisa catre client cu cuscces!\n");
				}
				else
				{
					send(clientSocket, answear, strlen(answear), 0);
					printf("Raspuns trimis catre client:  %s!\n", answear);
				}
			}
		}
		catch (const Exception& e)
		{
			std::cerr << "Eroare [" << e.getErrorCode() << "] cu mesajul: " + e.getMessage() + " ;\n";
			send(clientSocket, "NOK", strlen("NOK"), 0);
			if (e.getErrorCode() == 20) break;
			if (e.getErrorCode() == 21) break;
			continue;
		}
		
	}
	
	DataBase::getInstance().disconnect();


	// Close client socket
	closesocket(clientSocket);
}



