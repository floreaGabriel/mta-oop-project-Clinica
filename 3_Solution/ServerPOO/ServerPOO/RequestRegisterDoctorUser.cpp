#include "RequestRegisterDoctorUser.h"
#include "CUtils.h"
#include "DataBase.h"

RequestRegisterDoctorUser::RequestRegisterDoctorUser(std::string data) : RequestRegNormalUser(data)
{
	this->m_specializare = CUtils::understandData(data, '#')[8];
}

void RequestRegisterDoctorUser::manage_request()
{
	std::string string_cautare_dupa_username = "SELECT Nume FROM Doctors WHERE Username = '" + m_username + "'";

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
	std::string query = "INSERT INTO Doctors (Username, Nume, Prenume, Email, Password, PhoneNumber, CNP, Specializare) VALUES ('" + this->m_username + "','" + this->m_nume + "','" + this->m_prenume + "','" + this->m_email
		+ "','" + this->m_password + "','" + this->m_phoneNumber + "','" + this->m_CNP + "','" + m_specializare + "')";

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

