#include "CUtils.h"


std::vector<std::string> m_data;


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