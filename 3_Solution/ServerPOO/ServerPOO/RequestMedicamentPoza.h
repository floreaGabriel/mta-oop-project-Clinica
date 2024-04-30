#pragma once
#include "IRequest.h"

class RequestMedicamentPoza : public IRequest
{
public:
	RequestMedicamentPoza() {
		m_numePoza = nullptr;
	}
	RequestMedicamentPoza(std::string);

	void manage_request() override;
	char* manage_answear() override;
private:
	std::string m_numePoza;
	char* m_answear;
};

