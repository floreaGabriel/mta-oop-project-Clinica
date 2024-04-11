#pragma once

class ServerConnection
{
public:
	ServerConnection(int port)
	{
		start(port);
	}

	void start(int port);
	//int receive(char* receive, const int size) const;
private:
	int serverSocket;

	bool createSocket(int port);
	bool bindSocket(int port);
	bool listenForConnections();
	void handleClient(int);

};

