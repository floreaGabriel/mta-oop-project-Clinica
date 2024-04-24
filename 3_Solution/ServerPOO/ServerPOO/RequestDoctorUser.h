#pragma once

#include "RequestRegNormalUser.h"

class RequestDoctorUser : public RequestRegNormalUser
{
public:
	RequestDoctorUser() {
		m_specializare = nullptr;
	}

	RequestDoctorUser(std::string);
	~RequestDoctorUser() {}

	void manage_request() override;

private:
	
	std::string  m_specializare;
};

