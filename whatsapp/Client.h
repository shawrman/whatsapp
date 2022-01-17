#include "Helper.h"
#include <iostream>
#include <algorithm>
#pragma once


class Client
{
public:
	Client();
	Client(SOCKET socket);
	Client(SOCKET socket,string name);
	~Client();
	void run();
	void code200();
	void code204();

	void writeToFile(string SUser,string message);
	string readFromFile(string SUser);
	string dnames(); //return all names in alpahbetic order 
	void addToVector();
	SOCKET _socket;
	string _name;
	vector<Client*> *_clients;

};


