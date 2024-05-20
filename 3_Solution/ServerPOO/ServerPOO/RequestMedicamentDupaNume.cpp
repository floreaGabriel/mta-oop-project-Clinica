#include "RequestMedicamentDupaNume.h"
#include "CUtils.h"
#include "Exception.h"
#include "DataBase.h"

RequestMedicamentDupaNume::RequestMedicamentDupaNume(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');

	if (splitted_data[0] == "7")
		m_identifier = "7";
	else if (splitted_data[0] == "8")
		m_identifier = '8';

	m_numePoza = splitted_data[1];
}

void RequestMedicamentDupaNume::manage_request()
{
	if (m_identifier == "7")
	{
		std::string string_cautare = "select ImagineMedicament from Medicamente where NumeMedicament = '" + m_numePoza + "'";

		std::vector<std::wstring> preluare_result = DataBase::getInstance().selectQuery(std::wstring(string_cautare.begin(), string_cautare.end()));

		if (preluare_result.empty()) {
			throw Exception("Query-ul de SELECT de la Medicament 7# nu a selectat nimic!\n", 104);

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
	}
	else if (m_identifier == "8")
	{
		std::string string_cautare = "select NumeMedicament, ProviderMedicament, InformatiiSuplimentare, Pret, Prescriptie, Stoc from Medicamente where NumeMedicament = '" + m_numePoza + "'";
		std::vector<std::vector<std::wstring>> preluare_result = DataBase::getInstance().selectQuery3(std::wstring(string_cautare.begin(), string_cautare.end()));


		if (preluare_result.empty()) {
			throw Exception("Query-ul de SELECT de la Medicament 8# nu a selectat nimic!\n", 104);
		}
		else
		{
			std::string buffer_final = "8#";
			auto it = preluare_result.begin();
			for (it; it != preluare_result.end(); ++it)
			{
				for (auto col = (*it).begin(); col != (*it).end(); ++col)
				{
					buffer_final += std::string((*col).begin(), (*col).end());
					buffer_final += "#";
				}
			}
			m_answear = (char*)malloc((buffer_final.size() + 1) * sizeof(char));
			memcpy(m_answear, buffer_final.c_str(), buffer_final.size() + 1);
		}
	}

	return;
}

char* RequestMedicamentDupaNume::manage_answear()
{
	return m_answear;
}
