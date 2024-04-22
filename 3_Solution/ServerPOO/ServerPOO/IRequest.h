#pragma once
#include <iostream>
#include <string>

class IRequest
{
public:
	virtual void manage_request() = 0;
	virtual int manage_answear() = 0;

	class Factory {
	public:
		static IRequest* requestSelector(std::string);
	};
};

