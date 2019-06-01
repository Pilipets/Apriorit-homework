#include "TcpServer.h"

TcpServer::TcpServer(const string & ipAddress, int port) :
	m_ipAddress(ipAddress), m_port(port)
{
}

TcpServer::~TcpServer()
{
	CleanUp();
}

bool TcpServer::Init()
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);

	int wsInit = WSAStartup(ver, &data);
	//Inform caller the error that occured

	if (wsInit != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsInit << endl;
		return false;
	}
	return true;
}

void TcpServer::Run()
{
	char buf[MAX_BUFFER_SIZE];
	while (true)
	{
		// Create a listening socket
		SOCKET listening = CreateSocket();
		if (listening == INVALID_SOCKET)
			break;

		SOCKET client = WaitForConnection(listening);
		if (client != INVALID_SOCKET) {
			closesocket(listening);

			int length = 0;
			int bytesReceived;
			ZeroMemory(buf, MAX_BUFFER_SIZE);
			do {

				bytesReceived = recv(client, buf+length, MAX_BUFFER_SIZE-length, 0);
				if (bytesReceived > 0) {
					length += bytesReceived;
					//this->HandleReceivedMessage(client, string(buf, length));
				}
			} while (bytesReceived > 0);

			this->HandleReceivedMessage(client, string(buf, length));
		}
	}
}

void TcpServer::CleanUp()
{
	WSACleanup();
}

void TcpServer::HandleReceivedMessage(SOCKET socketId, const string & message)
{
	std::hash<string> hasher;
	cout << "Received: " << message << endl;
	cout << "Hash: " << hasher(message) << endl;
}

SOCKET TcpServer::CreateSocket()
{
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		return -1;
	}
	else {
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

		int  bindOK = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (bindOK != SOCKET_ERROR) {
			int listenOk = listen(listening, SOMAXCONN);
			if (listenOk == SOCKET_ERROR)
				return -1;
		}
		else
			return -1;
	}
	return listening;
}

SOCKET TcpServer::WaitForConnection(SOCKET listening)
{
	SOCKET client = accept(listening, NULL, NULL);
	return client;
}
