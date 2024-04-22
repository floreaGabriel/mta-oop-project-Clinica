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
		m_answear = 0;
	}
	RequestRegNormalUser(std::string);

	void manage_request() override;
	int manage_answear() override;

private:
	
	std::string m_nume;
	std::string m_prenume;
	std::string m_password;
	std::string m_email;
	std::string m_phoneNumber;
	std::string m_CNP;
	
	int m_answear;
};

