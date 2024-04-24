#pragma once
#include "IRequest.h"

class RequestRegNormalUser : public IRequest
{

public:
	RequestRegNormalUser() {
		m_nume = nullptr;
		m_prenume = nullptr;
		m_password = nullptr;
		m_email = nullptr;
		m_phoneNumber = nullptr;
		m_CNP = nullptr;
		m_answear = nullptr;
	}
	RequestRegNormalUser(std::string);
	~RequestRegNormalUser() {}
	void manage_request() override;
	char * manage_answear() override;

protected:
	
	std::string m_username;
	std::string m_nume;
	std::string m_prenume;
	std::string m_password;
	std::string m_email;
	std::string m_phoneNumber;
	std::string m_CNP;

	char * m_answear;
};

