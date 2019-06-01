#include<iostream>

#include "TcpClient.h"
using namespace std;

int main(int argc, char* argv[])
{
	//string filePath = "tmp.txt";
	TcpClient client(argv[1]);

	if (client.connectTo("127.0.0.1", 5400))
	{
		client.Run();
	}

	system("pause");
	return 0;
}