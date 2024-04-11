#include "Application.h"


int main(int argc, char argv[])
{

	Application::getInstance().getServer()->start(12345);
	// ana are mere
	return 0;
}