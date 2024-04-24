#include "Application.h"
#include "RequestDoctorUser.h"


int main(int argc, char argv[])
{

	Application::getInstance().getServer()->start(12345);
	return 0;
}