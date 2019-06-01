#include "TcpClient.h"
#include<fstream>


TcpClient::TcpClient(const string& filePath) : filePath(filePath)
{
	Init();
}


TcpClient::~TcpClient()
{
	CleanUp();
}

bool TcpClient::connectTo(const string & ipAddress, int port)
{
	m_sock = CreateSocket();
	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	int connResult = connect(m_sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(m_sock);
		return false;
	}
	return true;
}

void TcpClient::CleanUp()
{
	WSACleanup();
}

bool TcpClient::Init()
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &wsData);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return false;
	}
	return true;
}

void TcpClient::Run()
{
	cout << "> Started sending the file" << endl;
	ifstream fin(filePath);
	if (fin.is_open())
	{
		
		const size_t blockSize = 3;
		char buf[blockSize+1]; //small size was added intentionaly to ensure sending the file partially

		while (!fin.eof())
		{
			fin.read(buf, 3);
			buf[3] = '\0';
			cout << buf;
			int sendResult = send(m_sock, buf, blockSize + 1, 0);
			if(sendResult == SOCKET_ERROR)
			{
				cerr << "Server disconnected\n" << endl;
				return;
			}
		}
		fin.close();
	}
	else
		cerr << "Error in opening file" << filePath << endl;
	cout << endl;
	cout << "> Finished sending the file" << endl;
	CleanUp();
}

SOCKET TcpClient::CreateSocket()
{
	//Create a socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	return sock;
}
