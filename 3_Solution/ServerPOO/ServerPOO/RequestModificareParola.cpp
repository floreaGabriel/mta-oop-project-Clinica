#include "RequestModificareParola.h"
#include "CUtils.h"
#include "DataBase.h"
#include "Exception.h"
#include <vector>

RequestModificareParola::RequestModificareParola(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');

	m_username = splitted_data[1];
	m_parolaNoua = splitted_data[2];
}

void RequestModificareParola::manage_request()
{
	std::string query = " UPDATE NormalUsers SET Password = '" + m_parolaNoua + "' WHERE Username = '" + m_username + "';";

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

	return;

}

char* RequestModificareParola::manage_answear()
{
	return m_answear;
}
