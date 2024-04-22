#include "IRequest.h"
#include "CUtils.h"
#include "RequestRegNormalUser.h"

IRequest* IRequest::Factory::requestSelector(std::string data)
{
	int magicByte = stoi(CUtils::understandData(data, '#')[0]);

	switch (magicByte)
	{
	case 0:
		return new RequestRegNormalUser(data);
	default:
		break;
	}
}
