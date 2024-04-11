#pragma once
#include "ServerConnection.h"



// Singleton Aplicatie
class Application
{
public:

	static Application& getInstance();
	bool manageData(char*); // in functia asta controlezi datele primite de la client
	ServerConnection* getServer() { return m_appInstance->m_server; }

private:
	static Application* m_appInstance;
	ServerConnection* m_server = nullptr;


	bool manageLoginWindow(const char*);


	Application() = default;
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application&& operator=(Application&&) = delete;

	~Application();
};

