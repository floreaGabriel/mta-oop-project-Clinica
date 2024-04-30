#pragma once
#include "IRequest.h"
#include <iostream>

class RequestMedicamente : public IRequest
{
public:
	RequestMedicamente() {
		m_nrPagina = 0;
		m_answear = nullptr;   
	}
	RequestMedicamente(std::string);
	~RequestMedicamente() {}

	void manage_request() override;
	char* manage_answear() override;

private:


	int m_nrPagina;
	char* m_answear;
};

