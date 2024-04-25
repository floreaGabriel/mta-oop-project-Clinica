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
		m_answear = (char*)malloc(15 * sizeof(char));
		memcpy(m_answear, "OK", 15);
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
