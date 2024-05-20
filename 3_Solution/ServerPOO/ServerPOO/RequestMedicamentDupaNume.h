#pragma once
#include "IRequest.h"

class RequestMedicamentDupaNume : public IRequest
{
public:
	RequestMedicamentDupaNume() {
		m_numePoza = nullptr;
		m_answear = nullptr;
		m_identifier = nullptr;
	}
	RequestMedicamentDupaNume(std::string);

	void manage_request() override;
	char* manage_answear() override;
private:
	std::string m_identifier;
	std::string m_numePoza;
	char* m_answear;
};

