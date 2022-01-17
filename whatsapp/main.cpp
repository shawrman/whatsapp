
#include <exception>
#include "Helper.h"
#include "Server.h"
#include <iostream>
#include <string>
#include "WSAInitializer.h"
#pragma comment (lib, "ws2_32.lib")
#define PORT 8826
using std::string;
using std::cout;
using std::cin;
using std::endl;
int main()
{
	
	try
	{
	
		WSAInitializer wsaInit;		// so not destroy the port
		Server server(PORT);
		

	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;

}