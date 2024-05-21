#pragma once
#include "IRequest.h"

class RequestUpdateProgramare : public IRequest
{
public:
	RequestUpdateProgramare() {
		m_IDProgramare = nullptr;
		m_answear = nullptr;
	}
	RequestUpdateProgramare(std::string);
	~RequestUpdateProgramare() {}

	void manage_request() override;
	char* manage_answear() override;

private:

	std::string m_IDProgramare;

	char* m_answear;
};

