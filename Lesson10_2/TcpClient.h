#pragma once

#include<iostream>
#include<string>
#include<WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define MAX_BUFFER_SIZE (4096)
class TcpClient
{
public:
	TcpClient(const string& filePath);
	~TcpClient();

	bool connectTo(const string& ipAddress, int port);
	void CleanUp();
	
	void Run();
private:
	bool Init();
	SOCKET CreateSocket();

	string filePath;
	SOCKET m_sock;
};

