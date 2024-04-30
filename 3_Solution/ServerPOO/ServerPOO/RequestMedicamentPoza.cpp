#include "RequestMedicamentPoza.h"
#include "CUtils.h"
#include "Exception.h"
#include "DataBase.h"

RequestMedicamentPoza::RequestMedicamentPoza(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');

	m_numePoza = splitted_data[1];
}

void RequestMedicamentPoza::manage_request()
{
	std::string string_cautare = "select ImagineMedicament from Medicamente where NumeMedicament = '"+m_numePoza+"'";

	std::vector<std::wstring> preluare_result = DataBase::getInstance().selectQuery(std::wstring(string_cautare.begin(), string_cautare.end()));

	if (preluare_result.empty()) {
		throw Exception("Query-ul de SELECT de la programare nu a selectat nimic!\n", 104);

	}
	else
	{
		std::string buffer_final = "7#";
		auto it = preluare_result.begin();
		for (it; it != preluare_result.end(); ++it)
		{
			buffer_final += std::string((*it).begin(), (*it).end());
		}
		m_answear = (char*)malloc((buffer_final.size() + 1) * sizeof(char));
		memcpy(m_answear, buffer_final.c_str(), buffer_final.size() + 1);
	}

	return;
}

char* RequestMedicamentPoza::manage_answear()
{
	return m_answear;
}
