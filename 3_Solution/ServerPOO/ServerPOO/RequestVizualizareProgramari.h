#pragma once
#include "IRequest.h"
#include <vector>

class RequestVizualizareProgramari : public IRequest
{

public:
	RequestVizualizareProgramari() {
		m_username = nullptr;
		m_answear = nullptr;
	}
	RequestVizualizareProgramari(std::string);

	void manage_request() override;
	char* manage_answear() override;

private:
	std::vector<std::string> splitted_data;
	std::string m_username;
	char* m_answear;
};

