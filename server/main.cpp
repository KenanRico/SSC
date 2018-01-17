#include "serverutil.h"
#include "connection.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <vector>
#include <string>




std::vector<Connection*> connections;


bool initServerAttrib(int&, int&);
void initServerAddress(struct sockaddr_in&, int);
void serverLoop(int, int);
void checkNewConnection(int);
void closeAllConnections();


int main(){
	//specify server info (port, max number of clients, running state)
	int port_number = 0;
	int client_count = 0;
	//proceed to create socket if server is started
	if(initServerAttrib(port_number, client_count)){
		ServerUtil::log(ServerUtil::INFO, "Starting Server...\n");
		//create and open initial socket
		int initial_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(initial_socket>=0){
			//specify server address
			struct sockaddr_in server_addr;
			initServerAddress(server_addr, port_number);
			//bind initial socket to local address and port
			if(bind(initial_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))>=0){
				//server's loop. Main structure of whole program
				serverLoop(client_count, initial_socket);
			}else{
				ServerUtil::log(ServerUtil::ERROR, "Failed to bind initial socket!\n");
			}
		}else{
			ServerUtil::log(ServerUtil::ERROR, "Failed to create initial socket!\n");
		}
	}else{
		ServerUtil::log(ServerUtil::INFO, "Ending program...\n");
	}

	closeAllConnections();

	return 0;
}


bool initServerAttrib(int& p, int& c){
	bool start = false;
	ServerUtil::log(ServerUtil::PROMPT, "Start server? (y/n) \n");
	char s = ' ';
	std::cin>>s;
	if(s=='y'){
		start = true;
		ServerUtil::log(ServerUtil::INSTRUCTION, "Please enter port number: ");
		std::cin>>p;
		ServerUtil::log(ServerUtil::INSTRUCTION, "Please enter number of clients to support: ");
		std::cin>>c;
	}else if('n'){
		start = false;
	}else{
		ServerUtil::log(ServerUtil::ERROR, "Unrecognized option!\n");
		start = false;
	}

	return start;
}

void initServerAddress(struct sockaddr_in& server_addr, int port_number){
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port_number);
}

void serverLoop(int client_count, int initial_socket){
	while(true){
		if(connections.size()<client_count){
			checkNewConnection(initial_socket);
		}else{
			//client limit reached, no longer waiting for new connections
		}
		
	}
}

void checkNewConnection(int initial_socket){
	listen(initial_socket, 5);
	//create new thread when new connection comes in




	//code below is potentially incorrect


	Connection* new_client = new Connection(initial_socket);
	//the run function creates new thread and enters the main loop of the thread to handle messaging
	if(new_client->opened()){
		new_client->run();
		connections.push_back(new_client);
	}else{
		delete new_client;
	}
}

void closeAllConnections(){
	for(std::vector<Connection*>::iterator con=connections.begin(); con!=connections.end(); ++con){
		delete *con;
	}
}
