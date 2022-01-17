#include "Client.h"
#include <fstream>
#include <mutex>
#pragma once
using namespace std::this_thread;
using std::cout;
using std::cin;
using std::endl;
std::mutex fileMX;
Client::Client()		//c'tor
{
}
Client::Client(SOCKET socket) : _socket{socket}		 //c'tor
{

}
Client::Client(SOCKET socket, string name)	//c'tor
{
	_socket = socket;
	_name = name;
}

Client::~Client()		//d'tor
{
}

void Client::run()
{
	code200(); //start of coverstion
	
	while (true)
	{
		int code = Helper::getMessageTypeCode(_socket);	//type code
		switch (code)
		{
		case 200:
			code200();	//basicly will never happend 
			break;
		case 204:
			code204(); //update
			
			break;
		default:
			break;
		}

		//Helper::send_update_message_to_client(cS, "&MAGSH_MESSAGE&&Author&adir&DATA&hi:)&MAGSH_MESSAGE&&Author&bob&DATA&hi:)", "bob", s+"&bob");
		//Helper::send_update_message_to_client(_socket, "&MAGSH_MESSAGE&&Author&bob&DATA&hi:)&MAGSH_MESSAGE&&Author&bob&DATA&hi:)", "bob", s + "&bob");

		//cout << code << endl <<_name << endl;

															  
	}
}

void Client::code200()
{



	
	Helper::send_update_message_to_client(_socket, "", "", dnames());	//send with empty
}

void Client::writeToFile(string SUser, string message)		 //write to file the new message
{
	string fileName = "";
	if (strcmp(_name.c_str(), SUser.c_str()) > 0)
	{
		fileName += SUser + "&" + _name + ".txt";
	}
	else
	{
		fileName += _name + "&" + SUser + ".txt";

	}
	std::fstream file;

	file.open(fileName, std::ios_base::app | std::ios_base::in);
	string s = "&MAGSH_MESSAGE&&Author&" + _name + "&DATA&" + message;
	file << s;
	file.close();


}
string Client::readFromFile(string SUser)	   //read from file all measages
{
	string fileName = "";
	if (strcmp(_name.c_str(), SUser.c_str()) > 0)
	{
		fileName += SUser + "&" + _name + ".txt";
	}
	else
	{
		fileName += _name + "&" + SUser + ".txt";

	}
	std::ifstream file;

	file.open(fileName, std::ios_base::out);
	auto ss = std::ostringstream{};
	ss << file.rdbuf();
	file.close();
	return ss.str();
}

void Client::code204()			 //update methode
{
	int temp = Helper::getIntPartFromSocket(_socket, 2);
	string SUser = Helper::getStringPartFromSocket(_socket, temp);
	temp = Helper::getIntPartFromSocket(_socket, 5);
	string message = Helper::getStringPartFromSocket(_socket, temp);
	fileMX.lock();		//mutex so open one file at a time
	if (message != "")
	{
		writeToFile(SUser, message);

	}
	Helper::send_update_message_to_client(_socket, readFromFile(SUser), SUser, dnames());
	fileMX.unlock();


}

string Client::dnames()
{

	vector<string> Names;

	string temp = "";
	for (auto it = _clients->begin(); it != _clients->end(); it++)
	{

		Names.push_back( ((Client*)(*it))->_name);
	}
	std::sort(Names.begin(), Names.end());
	for (auto it = Names.begin(); it != Names.end(); it++)
	{

		temp += (*it) + "&";
	}
	
	if (temp.size() != 0)
	{
		temp.pop_back();
	}
	return temp;

}

void Client::addToVector()	 //push to vector
{
	_clients->push_back(this);
}
