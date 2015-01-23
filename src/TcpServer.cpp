/*
 * TcpServer.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: szsz
 */

#include "TcpServer.h"

TcpServer::TcpServer(int port)
{
	sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if(sock_descriptor < 0)
		printf("Failed creating socket\n");

	bzero((char *)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	serv_addr.sin_addr.s_addr = INADDR_ANY;

	serv_addr.sin_port = htons(port);

	if (bind(sock_descriptor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		printf("Failed to bind\n");

	listen(sock_descriptor, 5);

	printf("Waiting for connection...\n");
	size = sizeof(client_addr);
}

void TcpServer::AcceptClient()
{
	conn_desc = accept(sock_descriptor, (struct sockaddr *)&client_addr, &size);

	if (conn_desc == -1)
		printf("Failed accepting connection\n");
	else
		printf("Connected\n");
}


string TcpServer::Listen()
{
	string ss;
	int sizeMessage = 0;
	


	if(read(conn_desc, buff, MAX_SIZE) > 0)
	{
		ss = buff;		
		sizeMessage = atoi(ss.c_str());
		ss = "";

		printf("Ilosc danych otrzymanych %d\n",sizeMessage);

		do
		{
         		if(read(conn_desc, buff, MAX_SIZE) > 0)
			{
			 ss +=  buff;	
			}


		}
		while(ss.size() < sizeMessage);

		return ss;
	}
	else
		return "";
}

void TcpServer::Send(string messsage)
{
	write(conn_desc,messsage.c_str() ,messsage.size());
}

TcpServer::~TcpServer()
{
	close(conn_desc);
	close(sock_descriptor);
}

