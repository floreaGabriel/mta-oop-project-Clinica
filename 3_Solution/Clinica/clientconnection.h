#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H


class ClientConnection
{
public:
    static ClientConnection& getInstance();

    bool connectToServer(const char* ip, int port);
    bool sendData(const char *);
    bool receiveData(char* buffer, int buffSize);

private:

    int m_clientSocket;
    static ClientConnection* m_instance;


    ClientConnection() = default;
    ClientConnection(const ClientConnection&) = delete;
    ClientConnection(ClientConnection&&) = delete;
    ClientConnection& operator=(const ClientConnection&) = delete;

    ~ClientConnection();
};

#endif // CLIENTCONNECTION_H
