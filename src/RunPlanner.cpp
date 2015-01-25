//============================================================================
// Name        : RunPlanner.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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

#include "TcpServer.h";

using namespace std;

string runPlanner(string plannerPath)
{
	string s;
	FILE *handle = popen(plannerPath.c_str(), "r");
	char buf[10000];

	if (handle == NULL)
		return NULL;

	fread(buf, 1, sizeof(buf), handle);
	pclose(handle);
	s = buf;

	return s;
}

void saveToFile(string sMap,string sPath)
{
	ofstream myfile;
	myfile.open(sPath.c_str(),ios::trunc);
	myfile << sMap;
	myfile.close();
}

string getPlanForRobots(string sMap,string sPath,string plannerPath)
{
	saveToFile(sMap,sPath);

	return runPlanner(plannerPath);
}

int main()
{
	string sPathJSON = "../../MazeRobo.roson";
	string plannerPath =  "python ../../solver.py " + sPathJSON;

	//string plannerPath =  "python ../../solver.py ../../MazeRoboLabFullMap_graphSimpleKopia.roson";

	while(true)
	{
		TcpServer *tcp = new TcpServer(13000);
			string sMapJSON;
			string message;
			string sPlan;
			bool isClientConnected = false;


		isClientConnected = false;

		printf("Oczekuje na klienta\n");

		tcp->AcceptClient();
		printf("Klient polaczony\n");
		isClientConnected = true;	
		
		sMapJSON = tcp->Listen();

		if(sMapJSON.size() > 0)
		{
			printf( "Otrzymano%s\n", sMapJSON.c_str());
			sPlan = getPlanForRobots(sMapJSON,sPathJSON,plannerPath);

			printf( "Wygenerowano %s\n", sPlan.c_str());

			tcp->Send(sPlan);

			printf("Wyslano sPlan\n");
			fflush(NULL);
		}
		tcp->Close();

		delete tcp;
	}

/*
	while(true)
	{
		isClientConnected = false;

		printf("Oczekuje na klienta\n");

		tcp->AcceptClient();

		printf("Klient polaczony\n");

		isClientConnected = true;

		do
		{
			try
			{
				sMapJSON = tcp->Listen();

				if(sMapJSON.size() > 0)
				{
					printf( "Otrzymano%s\n", sMapJSON.c_str());

					sPlan = getPlanForRobots(sMapJSON,sPathJSON,plannerPath);

					printf( "Wygenerowano %s\n", sPlan.c_str());

					tcp->Send(sPlan);

					printf("Wyslano sPlan\n");

					fflush(NULL);
				}
				else
					isClientConnected = false;
			}
			catch(...)
			{
				isClientConnected = false;
			}
		}
		while(isClientConnected);
	}
*/
	return 0;
}







