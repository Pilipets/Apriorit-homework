#include<iostream>

#include "TcpServer.h"
using namespace std;

int main(int argc, char* argv[])
{
	TcpServer server("127.0.0.1", 5400);

	if (server.Init())
	{
		server.Run();
	}
	return 0;
}