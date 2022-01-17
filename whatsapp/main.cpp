
#include <exception>
#include "Helper.h"
#include "Server.h"
#include <iostream>
#include <string>
#include "WSAInitializer.h"
#include <fstream>
#include <string>

#pragma warning(disable:4996)



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
		string line = "";
		std::ifstream input_file("config.txt");
		WSAInitializer wsaInit;		// so not destroy the port
		getline(input_file, line);
		getline(input_file, line);
		char str[9]; // declare a ptr pointer
		strcpy(str, line.c_str());
		char* ptr;
		ptr = strtok(str , "=");
		ptr = strtok(NULL, "=");
		Server server(atoi(ptr));
	
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;

}