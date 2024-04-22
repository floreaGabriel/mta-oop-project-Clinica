#include "RequestRegNormalUser.h"
#include "DataBase.h"
#include "CUtils.h"



RequestRegNormalUser::RequestRegNormalUser(std::string data)
{
	std::vector<std::string> splitted_data = CUtils::understandData(data, '#');
	this->m_nume = splitted_data[1];
	this->m_prenume = splitted_data[2];
	this->m_password = splitted_data[3];
	this->m_email = splitted_data[4];
	this->m_phoneNumber = splitted_data[5];
	this->m_CNP = splitted_data[6];

}

void RequestRegNormalUser::manage_request()
{
	bool flag = DataBase::getInstance().executeQuery("SELECT * FROM NormalUsers");

	if (flag)
	{
		m_answear = 1;
	}
	else
	{
		m_answear = 0;
	}
}

int RequestRegNormalUser::manage_answear()
{
	return this->m_answear;
}
