#include "CUtils.h"
#include "DataBase.h"
#include "Exception.h"

#include <iostream>
#include <string>



std::vector<std::string> CUtils::understandData(std::string data, char delimiter)
{
	std::string tmp{}; // stocheaza temporar fiecare cuvant inteles
	std::vector<std::string> words; // vom returna cuvintele separate

	for (int i = 0; i < data.size() ; i++) // verificam byte cu byte daca este delimitator sau nu
	{
		if (data[i] != delimiter)
		{
			tmp += data[i];
		}
		else
		{
			words.push_back(tmp);
			tmp = "";
		}
	}

	words.push_back(tmp); // adaug ultimul cuvant deoarece la final nu mai are #

	return words;
}

std::string extractNumePrenumeCnp(std::string specializare, std::string data, int id)
{

	std::string string_cautare = "SELECT d.Nume, d.Prenume, d.CNP FROM ProgramDoctori pd INNER JOIN Doctors d ON pd.IDDoctor = d.ID WHERE d.Specializare = '" + specializare + "' AND pd.Data = '" + data + "' AND pd.IDDoctor = " + to_string(id);

	std::vector<std::vector<std::wstring>> select_result =
		DataBase::getInstance().selectQuery2(
			std::wstring(string_cautare.begin(), string_cautare.end())
		);

	std::string de_trimis;

	// Verifică dacă există cel puțin un rând în rezultatele selectate
	if (select_result.empty()) { throw Exception("Nu exista niciun rand in tabela selectata!\n", 104); }
	// Verifică dacă primul rând conține cel puțin un element
	if (select_result[0].empty()) { throw Exception("Primul rand din tabela selectat nu contine niciun cuvant!\n", 104); }
	// Iterează prin elementele primului rând și construiește șirul de trimis
	for (const auto& it : select_result[0])
	{
		de_trimis += std::string(it.begin(), it.end());
		de_trimis += "#";
	}



	return de_trimis;

}
std::vector<std::string> CUtils::selectDataForProgramari(std::vector<std::vector<std::wstring>> select_result, std::string specializare, std::string data)
{
	std::vector<std::string> dateDoctoriProgramari;
	for (const auto& row : select_result)
	{
		std::string date = extractNumePrenumeCnp(specializare, data, atoi(std::string(row[0].begin(), row[0].end()).c_str()));
		std::string creare_raspuns = "4#" + date;
		int i = 0;
		for (auto it = row.begin(); it != row.end(); ++it)
		{
			if (i == 0 || i == 1) { i++; continue; } // sa imi sara peste primul element
			creare_raspuns += std::string(it->begin(), it->end());
			if (std::next(it) != row.end())
				creare_raspuns += "#";
		}
		dateDoctoriProgramari.push_back(creare_raspuns);
	}

	return dateDoctoriProgramari;
}
