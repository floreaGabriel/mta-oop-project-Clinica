#pragma once
#include "IRequest.h"

class RequestModificareParola : public IRequest
{
public:
	RequestModificareParola() {
		m_username = nullptr;
		m_parolaNoua = nullptr;
		m_answear = nullptr;
		m_tip = nullptr;
	}
	RequestModificareParola(std::string);

	void manage_request() override;
	char* manage_answear() override;

private:

	std::string m_username;
	std::string m_parolaNoua;
	std::string m_tip;
	char* m_answear;
};

