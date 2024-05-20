#include "RequestMedicamente.h"
#include "CUtils.h"
#include "DataBase.h"
#include <string>
#include "Exception.h"

RequestMedicamente::RequestMedicamente(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');

	m_nrPagina = atoi(splitted_data[1].c_str()); // primesc 6#1 si transform 1 in int
}

void RequestMedicamente::manage_request()
{

	std::string string_cautare = "select NumeMedicament, Pret from Medicamente where IDMedicament between "+ std::to_string(m_nrPagina * 6 + 1) + " and " + std::to_string(m_nrPagina * 6 + 6) + ";";

	std::vector<std::vector<std::wstring>> preluare_result = DataBase::getInstance().selectQuery3(std::wstring(string_cautare.begin(), string_cautare.end()));
	
	if (preluare_result.empty()) {
		throw Exception("Query-ul de SELECT de la programare nu a selectat nimic!\n", 104);

	}
	else
	{
		std::string buffer_final = "6";
		auto it = preluare_result.begin();
		for (it ; it != preluare_result.end(); ++it)
		{
			buffer_final += "$";
			for (auto col : *it)
			{
				buffer_final += std::string(col.begin(), col.end());
				buffer_final += "#";
			}

		}
		m_answear = (char*)malloc((buffer_final.size() + 1) * sizeof(char));
		memcpy(m_answear, buffer_final.c_str(), buffer_final.size() + 1);
	}


	return;
}

char* RequestMedicamente::manage_answear()
{
	return m_answear;
}
