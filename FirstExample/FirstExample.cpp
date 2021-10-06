// FirstExample.cpp : Defines the entry point for the application.
//

#include "FirstExample.h"
#include <boost/asio.hpp>

int main()
{
	int teste[10];
	for (int i = 0; i <= 10; i++) {
		teste[i] = i;
	}
	std::cout << "Hello CMake." << std::endl;
	return 0;
}
