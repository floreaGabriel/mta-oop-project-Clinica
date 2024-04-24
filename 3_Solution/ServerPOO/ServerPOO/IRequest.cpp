#include "IRequest.h"
#include "CUtils.h"
#include "RequestRegNormalUser.h"
#include "RequestDoctorUser.h"
#include "RequestLoginNormalUser.h"
#include "RequestLoginDoctor.h"

IRequest* IRequest::Factory::requestSelector(std::string data)
{
	int magicByte = stoi(CUtils::understandData(data, '#')[0]);

	switch (magicByte)
	{
	case 0:
		// 0#username#nume#prenume#email#parola#telefon#CNP
		return new RequestRegNormalUser(data);
	case 1:
		// 1#username#nume#prenume#email#parola#telefon#CNP#specializare
		return new RequestDoctorUser(data);
	case 2: 
		// 2#useranme#parola
		return new RequestLoginNormalUser(data);
	case 3:
		// 3#username#paraola
		return new RequestLoginDoctor(data);
	default:
		break;
	}
}
