#include "RequestRegisterProgramare.h"
#include "CUtils.h"
#include "DataBase.h"

RequestRegisterProgramare::RequestRegisterProgramare(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');
	this->m_CNPPacient = splitted_data[1];
	this->m_CNPDoctor = splitted_data[2];
	this->m_data = splitted_data[3];
	this->m_ora = splitted_data[4];
	this->m_motiv = splitted_data[5];
}

void RequestRegisterProgramare::manage_request()
{
	// inserare in tabelul de programari
	std::string query = "INSERT INTO [LoginAccounts].[dbo].[Programari] ([IDDoctor], [IDPacient], [Data], [IntervalOrar], [Motiv]) VALUES( (SELECT[ID] FROM[LoginAccounts].[dbo].[Doctors] WHERE[CNP] = '"+ m_CNPDoctor +"'), (SELECT[ID] FROM[LoginAccounts].[dbo].[NormalUsers] WHERE[CNP] = '"+ m_CNPPacient +"'), '" + m_data + "','" + m_ora +"','" + m_motiv + "');";
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
