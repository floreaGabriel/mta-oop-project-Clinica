#include "RequestRegNormalUser.h"
#include "DataBase.h"
#include "CUtils.h"
#


RequestRegNormalUser::RequestRegNormalUser(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');
	this->m_username = splitted_data[1];
	this->m_nume = splitted_data[2];
	this->m_prenume = splitted_data[3];
	this->m_email = splitted_data[4];
	this->m_password = splitted_data[5];
	this->m_phoneNumber = splitted_data[6];
	this->m_CNP = splitted_data[7];
}

void RequestRegNormalUser::manage_request()
{
	std::string string_cautare_dupa_username = "SELECT NUME FROM NormalUsers WHERE Username = '" + m_username + "'";

	// Caut in baza de date daca exista deja userul
	std::vector<std::wstring> select_result = DataBase::getInstance().selectQuery(std::wstring(string_cautare_dupa_username.begin(), string_cautare_dupa_username.end()));

	// Daca exista trimit mesaj la client ca deja exista acest user
	if (select_result.size() != 0) 
	{
		cout << "User already exists!\n";
		m_answear = (char*)malloc(15 * sizeof(char));
		memcpy(m_answear, "ALREADY EXISTS", 15);
		return;
	}
	
	// Daca nu exista il inserez in baza de date
	std::string query = "INSERT INTO NormalUsers (Username, Nume, Prenume, Email, Password, PhoneNumber, CNP) VALUES ('" + this->m_username + "','" + this->m_nume + "','" + this->m_prenume + "','" + this->m_email
		+ "','" + this->m_password + "','" + this->m_phoneNumber + "','" + this->m_CNP + "')";

	std::wstring wquery(query.begin(), query.end());
	 
	bool flag = DataBase::getInstance().executeQuery(wquery);

	// verific daca userul a fost inserat cu succes
	if (flag)
	{
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

char * RequestRegNormalUser::manage_answear()
{
	return this->m_answear;
}
