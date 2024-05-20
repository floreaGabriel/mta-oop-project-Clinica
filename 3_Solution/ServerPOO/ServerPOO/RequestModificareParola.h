#pragma once
#include "IRequest.h"

class RequestModificareParola : public IRequest
{
public:
	RequestModificareParola() {
		m_username = nullptr;
		m_parolaNoua = nullptr;
		m_answear = nullptr;
	}
	RequestModificareParola(std::string);

	void manage_request() override;
	char* manage_answear() override;

private:

	std::string m_username;
	std::string m_parolaNoua;

	char* m_answear;
};

