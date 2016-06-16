#include<stdio.h>
#include<stdio.h>
#include<WinSock2.h>
#include<iostream>
#pragma  comment (lib,"ws2_32.lib")

int main(void)
{
	WSADATA data;
	SOCKADDR_IN serverSockAddr, clientSockAddr;
	SOCKET serverSocket, clientSocket;
	int addrlen = sizeof(SOCKADDR_IN);
	int status, numrcv;
	char buffer[256] = {};

	//��ʼ��windows socket dll
	status = WSAStartup(MAKEWORD(1, 1), &data);
	if (status != 0)
		std::cout << "Windows socket dll init fails" << std::endl;
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	serverSockAddr.sin_port = htons(8899);
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
		std::cout << "build socket fails" << std::endl;
	//��socket���ض���ַ(�ṹ���ַ)
	status = bind(serverSocket, (LPSOCKADDR)&serverSockAddr, sizeof(serverSockAddr));
	if (SOCKET_ERROR == status)
		std::cout << "bind addr fails" << std::endl;

	//�������������������󣬻���˵���Ǽ���
	status = listen(serverSocket/*�׽��ֺ�*/, 2/*����������ӵ��׽��ָ���*/);
	if (SOCKET_ERROR == status)
		std::cout << "listen fails" << std::endl;
	//�������������Ǿͽ�����������
	std::cout << "waitting connection" << std::endl;
	clientSocket = accept(serverSocket, (LPSOCKADDR) & clientSocket, &addrlen);
	std::cout << "connected!" << std::endl;
	while (true)
	{
		numrcv = recv(clientSocket, buffer, 256, 0);
		if (strlen(buffer) != 0)
		{
			std::cout << buffer << std::endl;
			memset(buffer, 0, 256 * sizeof(char));
		}
	}
	closesocket(serverSocket);//�ر�����
	WSACleanup();
}