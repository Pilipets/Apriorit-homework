#pragma once
#include<iostream>
#include<string>
#include<WS2tcpip.h> //Header file for Winsock functions
#pragma comment (lib, "ws2_32.lib") //Winsock library code

#define MAX_BUFFER_SIZE (4096)
using namespace std;
class TcpServer {

public:
	TcpServer(const string& ipAddress, int port);
	~TcpServer();

	bool Init(); //Initialize winsock
	void Run(); //The main processing loop
	void CleanUp();
private:
	void HandleReceivedMessage(SOCKET socketId, const string& message);
	SOCKET CreateSocket();
	SOCKET WaitForConnection(SOCKET listening);

	string m_ipAddress;
	int m_port;
};