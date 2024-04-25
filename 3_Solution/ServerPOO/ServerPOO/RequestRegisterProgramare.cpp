#include "RequestRegisterProgramare.h"
#include "CUtils.h"
#include "DataBase.h"

RequestRegisterProgramare::RequestRegisterProgramare(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');
	this->m_numePacient = splitted_data[1];
	this->m_prenumePacient = splitted_data[2];
	this->m_CNPPacient = splitted_data[3];
	this->m_numeDoctor = splitted_data[4];
	this->m_prenumeDoctor = splitted_data[5];
	this->m_CNPDoctor = splitted_data[6];
	this->m_data = splitted_data[7];
	this->m_ora = splitted_data[8];
	this->m_motiv = splitted_data[9];
}

void RequestRegisterProgramare::manage_request()
{
	std::string query = "INSERT INTO Programari ([Nume Pacient], [Prenume Pacient], [CNP Pacient], [Nume Doctor], [Prenume Doctor], [CNP Doctor], Data, Ora, Motiv) VALUES ('" + this->m_numePacient + "','" + this->m_prenumePacient + "','" + this->m_CNPPacient + "','" + this->m_numeDoctor
		+ "','" + this->m_prenumeDoctor + "','" + this->m_CNPDoctor + "','" + this->m_data + "','" + this->m_ora + "','" + this->m_motiv + "')";

	std::wstring wquery(query.begin(), query.end());

	bool flag = DataBase::getInstance().executeQuery(wquery);

	if (flag)
	{
		std::cout << "Programarea a fost inserata in baza de date!\n";
		m_answear = (char*)malloc(3 * sizeof(char));
		memcpy(m_answear, "OK", 3);
	}
	else
	{
		m_answear = (char*)malloc(4 * sizeof(char));
		memcpy(m_answear, "NOK", 4);
	}

	return;
}

char* RequestRegisterProgramare::manage_answear()
{
	return m_answear;
}
