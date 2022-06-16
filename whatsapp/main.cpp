
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
		WSAInitializer wsaInit;		// have to be before using windwos scokets
		getline(input_file, line);
		getline(input_file, line);
		char str[9]; 
		strcpy(str, line.c_str());
		char* ptr;
		ptr = strtok(str , "=");
		ptr = strtok(NULL, "=");
		Server server(atoi(ptr));
	
	}
	catch (...)
	{
		std::cout << "Error occured: "  << std::endl;
	}
	system("PAUSE");
	return 0;

}