#include "Server.h"
#include "Client.h"
#include <mutex>
#pragma once
vector<Client*> clients;

Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

Server::Server(int port)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
	serve(port);
}

void Server::serve(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;
	
	//while (true)
	//{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
	std::cout << "Waiting for client connection request" << std::endl;
	acceptClient();
	//}
	
}

SOCKET Server::getSocket()
{
	return _serverSocket;
}


void Server::acceptClient()
{
	          // mutex for critical section
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server

	while (true)
	{
		SOCKET sc = accept(_serverSocket, NULL, NULL);

		std::thread bla([&] { clientHandler(sc); });	//try mutex
		bla.detach();
		std::cout << "Client accepted. Server and client can speak" << std::endl;
	}
	
	//std::string s = Helper::getStringPartFromSocket(_serverSocket, 4);
	// the function that handle the conversation with the client


}


void Server::clientHandler(SOCKET cS)
{
	try					  //two tries so the client be in the bigger scope
	{
		int code = Helper::getMessageTypeCode(cS);

		int temp = Helper::getIntPartFromSocket(cS, 2);
		string s = Helper::getStringPartFromSocket(cS, temp);
		Client* thisClient = new Client(cS, s); 
		try
		{

			thisClient->_clients = &clients;
			thisClient->addToVector();
			//send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
			thisClient->run();






			// Closing the socket (in the level of the TCP protocol)
			closesocket(cS);
		}
		catch (const std::exception& e)			//client disconncted
		{
			for (auto it = clients.begin(); it != clients.end(); it++)
			{

				if ((*it)->_name == thisClient->_name)
				{
					clients.erase(it);
					break;
				}
			}
			closesocket(cS);

		}
	}
	catch (...)
	{

	}
	


}