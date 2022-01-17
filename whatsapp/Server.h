#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include "Helper.h"
#include <vector>
#pragma once


class Server
{
public:
	Server();
	~Server();
	Server(int port);
	void serve(int port);
	SOCKET getSocket();
	


	void acceptClient();
	void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;
};
