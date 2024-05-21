#include "RequestUpdateProgramare.h"
#include "CUtils.h"
#include "DataBase.h"
#include "Exception.h"
#include <vector>

RequestUpdateProgramare::RequestUpdateProgramare(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');

	m_IDProgramare = splitted_data[1];
}

void RequestUpdateProgramare::manage_request()
{
	std::string query = " UPDATE Programari SET Finalizat= 'da' WHERE IDProgramare = '" + m_IDProgramare + "';";

	std::wstring wquery(query.begin(), query.end());

	bool flag = DataBase::getInstance().executeQuery(wquery);

	if (flag) {
		m_answear = (char*)malloc(3 * sizeof(char));
		memcpy(m_answear, "OK", 3);
	}
	else
	{
		m_answear = (char*)malloc(4 * sizeof(char));
		memcpy(m_answear, "NOK", 4);
	}
}

char* RequestUpdateProgramare::manage_answear()
{
	return m_answear;
}

