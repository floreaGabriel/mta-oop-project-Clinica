#pragma once

#include "IRequest.h"

class RequestRegisterProgramare : public IRequest
{
public:
	RequestRegisterProgramare() {
		m_numePacient = nullptr;
		m_prenumePacient = nullptr;
		m_CNPPacient = nullptr;
		m_numeDoctor = nullptr;
		m_prenumeDoctor = nullptr;
		m_CNPDoctor = nullptr;
		m_data = nullptr;
		m_ora = nullptr;
		m_motiv = nullptr;
	}
	RequestRegisterProgramare(std::string);
	~RequestRegisterProgramare();

	void manage_request() override;
	char* manage_answear() override;

private:

	std::string m_numePacient;
	std::string m_prenumePacient;
	std::string m_CNPPacient;
	std::string m_numeDoctor;
	std::string m_prenumeDoctor;
	std::string m_CNPDoctor;
	std::string m_data;
	std::string m_ora;
	std::string m_motiv;

	char* m_answear;
};