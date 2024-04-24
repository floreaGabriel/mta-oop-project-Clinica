#pragma once
#include "IRequest.h"

class RequestLoginNormalUser : public IRequest
{
public:

	RequestLoginNormalUser()
	{
		m_username = nullptr;
		m_password = nullptr;
		m_answear = nullptr;
	}

	// am ramas aici trebuie sa continui sa faci login requestul
	RequestLoginNormalUser(std::string);
	~RequestLoginNormalUser() {}
	void manage_request() override;
	char* manage_answear() override;

private:

	std::string m_username;
	std::string m_password;

	char* m_answear;
};

