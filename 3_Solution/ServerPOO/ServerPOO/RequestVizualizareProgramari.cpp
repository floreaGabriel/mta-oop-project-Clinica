#include "RequestVizualizareProgramari.h"
#include "CUtils.h"
#include "DataBase.h"
#include "Exception.h"




RequestVizualizareProgramari::RequestVizualizareProgramari(std::string data)
{
	splitted_data = CUtils::understandData(data, '#');
	m_username = splitted_data[1];
}

void RequestVizualizareProgramari::manage_request()
{
	std::string string_cautare;
	
	if (splitted_data[0] == "10")
		string_cautare = "select p.IDProgramare, D.Nume, p.Data, p.IntervalOrar, p.Motiv, p.Finalizat from Programari p inner join NormalUsers n on n.ID = p.IDPacient inner join Doctors d on d.ID = p.IDDoctor where n.Username = '"+m_username+"'";
	else if (splitted_data[0] == "11")
		string_cautare = "select p.IDProgramare, n.Nume, p.Data, p.IntervalOrar, p.Motiv, p.Finalizat from Programari p inner join NormalUsers n on n.ID = p.IDPacient inner join Doctors d on d.ID = p.IDDoctor where d.Username = '"+m_username+"'";
	
	std::vector<std::vector<std::wstring>> preluare_result = DataBase::getInstance().selectQuery3(std::wstring(string_cautare.begin(), string_cautare.end()));


	if (preluare_result.empty()) {
		throw Exception("Query-ul de SELECT de la vizualizare programare nu a selectat nimic!\n", 104);
	}
	else 
	{

		std::string buffer_final;
		
		if (splitted_data[0] == "10")
			buffer_final = "10";
		else if (splitted_data[0] == "11")
			buffer_final = "11";

		auto it = preluare_result.begin();
		for (it; it != preluare_result.end(); ++it)
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

char* RequestVizualizareProgramari::manage_answear()
{
	return m_answear;
}
