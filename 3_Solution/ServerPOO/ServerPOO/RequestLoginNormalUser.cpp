#include "RequestLoginNormalUser.h"
#include "CUtils.h"
#include "DataBase.h"
#include <iostream>

RequestLoginNormalUser::RequestLoginNormalUser(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');
	this->m_username = splitted_data[1];
	this->m_password = splitted_data[2];
}

void RequestLoginNormalUser::manage_request()
{
	std::string string_cautare_dupa_username = "SELECT NUME FROM NormalUsers WHERE Username = '" + m_username + "' AND Password = '"+m_password +"'";

	// Caut in baza de date daca exista deja userul
	std::vector<std::wstring> select_result = DataBase::getInstance().selectQuery(std::wstring(string_cautare_dupa_username.begin(), string_cautare_dupa_username.end()));

	// Daca exista trimit mesaj la client ca deja exista acest user
	// !!!!!!!!!!!!!! trimite datele userului
	if (select_result.size() != 0)
	{
		std::string result(select_result[0].begin(), select_result[0].end());
		cout << "User exists!\n" << result << " s-a logat!\n" ;

		// dupa ce s-a logat trimit clientului toate datele lui pentru a le avea pe toata durata sesiunii
		std::string buffer_final = "2#";
		std::string preluare_date_pacient = "SELECT * FROM NormalUsers WHERE Username = '" + m_username + "'";
		std::vector<std::vector<std::wstring>> preluare_result = DataBase::getInstance().selectQuery2(std::wstring(preluare_date_pacient.begin(), preluare_date_pacient.end()));

		for (auto it : preluare_result)
		{
			int i = 0;
			for (auto col = it.begin(); col != it.end(); ++col)
			{
				if (i == 0) { i++; continue; }
				buffer_final += std::string((*col).begin(), (*col).end());
				buffer_final += "#";
			}
		}

		
		m_answear = (char*)malloc(((buffer_final.size() + 1) * sizeof(char)));
		memcpy(m_answear, buffer_final.c_str(), buffer_final.size() + 1);
		return;
	}
	else
	{
		m_answear = (char*)malloc(4 * sizeof(char));
		memcpy(m_answear, "NOK", 4);
	}

	return;
}

char* RequestLoginNormalUser::manage_answear()
{
	return this->m_answear;
}
