#pragma once
#include "IRequest.h"
#include <iostream>
#include <vector>

class RequestProgramare : public IRequest
{
public:

	RequestProgramare() {
		this->m_specializare = nullptr;
		this->m_data = nullptr;
		this->m_answear = nullptr;
	}
	RequestProgramare(std::string);
	~RequestProgramare() {}

	void manage_request() override;
	char* manage_answear() override;
	std::vector<std::string> getMTOSend() { return m_to_send; }
private:

	std::string m_specializare;
	std::string m_data;
	
	std::vector <std::string> m_to_send;
	char * m_answear;

};

