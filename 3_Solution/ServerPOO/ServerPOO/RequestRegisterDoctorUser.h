#pragma once

#include "RequestRegNormalUser.h"

class RequestRegisterDoctorUser : public RequestRegNormalUser
{
public:
	RequestRegisterDoctorUser() {
		m_specializare = nullptr;
	}

	RequestRegisterDoctorUser(std::string);
	~RequestRegisterDoctorUser() {}

	void manage_request() override;

private:
	
	std::string  m_specializare;
};

