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

	int optval = 1;

	if (setsockopt(sock_descriptor,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) == -1)
	{
		 printf("Setsockopt\n");
	}

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
	string temp;

	int sizeMessage = 0;
	int size = 0;
	

	if( (size = read(conn_desc, buff, MAX_SIZE)) > 0)
	{
		temp = buff;
		ss = temp.substr(0,size);
		sizeMessage = atoi(ss.c_str());
		printf("Dane Ilosc danych %d\n",size);
		ss = "";

		printf("Ilosc danych otrzymanych %d\n",sizeMessage);

		do
		{
         		if((size = read(conn_desc, buff, MAX_SIZE)) > 0)
			{
         			printf("Petla Ilosc danych %d\n",size);

         	 temp = buff;
			 ss +=  temp.substr(0,size);
			}

         		printf("ss.size() %d\n", ss.size());
		}
		while(ss.size() != sizeMessage);

		return ss;
	}
	else
		return "";
}

void TcpServer::Send(string messsage)
{
	write(conn_desc,messsage.c_str() ,messsage.size());
}

void TcpServer::Close()
{
	//close(conn_desc);
//	close(sock_descriptor);
}

TcpServer::~TcpServer()
{
	close(conn_desc);
	close(sock_descriptor);
}

