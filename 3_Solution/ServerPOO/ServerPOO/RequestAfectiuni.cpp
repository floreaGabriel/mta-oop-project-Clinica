#include "RequestAfectiuni.h"
#include "CUtils.h"
#include "DataBase.h"
#include "Exception.h"
#include <vector>
#include <string>

RequestAfectiuni::RequestAfectiuni(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');

	m_text = splitted_data[1];
}

std::vector<std::vector<std::wstring>> cautare_in_matrice(const std::vector<std::vector<std::wstring>>& matrice, const std::string& cautat)
{
	std::vector<std::vector<std::wstring>> rezultat;

	for (const auto& rand : matrice)
	{
		if (rand.size() > 1 && std::string(rand[1].begin(),rand[1].end()).find(cautat) != std::string::npos)
		{
			rezultat.push_back(rand);
		}
	}

	return rezultat;
}

void RequestAfectiuni::manage_request()
{
	// TO DO .....
	std::string string_cautare = "select * from Afectiuni";
	std::vector<std::vector<std::wstring>> preluare_result = DataBase::getInstance().selectQuery3(std::wstring(string_cautare.begin(), string_cautare.end()));
	

	if (preluare_result.empty()) {
		throw Exception("Query-ul de SELECT de la afectiuni nu a selectat nimic!\n", 104);
	}
	else
	{
		std::vector<std::vector<std::wstring>> rezultate = cautare_in_matrice(preluare_result, m_text);

		std::string buffer_final = "12";
		auto it = rezultate.begin();
		for (it; it != rezultate.end(); ++it)
		{
			buffer_final += "$";
			int i = 0;
			for (auto col : *it)
			{
				if (i == 0) { i++; continue; }
				buffer_final += std::string(col.begin(), col.end());
				buffer_final += "#";
			}

		}
		m_answear = (char*)malloc((buffer_final.size() + 1) * sizeof(char));
		memcpy(m_answear, buffer_final.c_str(), buffer_final.size() + 1);

	}


	return;

}

char* RequestAfectiuni::manage_answear()
{
	return m_answear;
}


