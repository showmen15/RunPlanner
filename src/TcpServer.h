/*
 * TcpServer.h
 *
 *  Created on: Jan 21, 2015
 *      Author: szsz
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_


#include <iostream>
#include <stdio.h>

#include <string>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50000

using namespace std;

class TcpServer {
private:
	int sock_descriptor, conn_desc;

	struct sockaddr_in serv_addr, client_addr;

	unsigned int size;
	char buff[MAX_SIZE];

public:
	TcpServer(int port);
	string Listen();
	void Send(string messsage);
	void AcceptClient();
	virtual ~TcpServer();
	void Close();
	
};

#endif /* TCPSERVER_H_ */
