#pragma once
#include "IRequest.h"

class RequestAfectiuni : public IRequest
{
public:
	RequestAfectiuni() {
		m_text = nullptr;
		m_answear = nullptr;
	}
	RequestAfectiuni(std::string);

	void manage_request() override;
	char* manage_answear() override;

private:
	std::string m_text;
	char* m_answear;
};

