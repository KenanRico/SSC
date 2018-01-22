#include "connection.h"
#include "serverutil.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <vector>
#include <string>


Connection::Connection(int init_sock){ 
	socket_info.client_length = sizeof(socket_info.client_addr);
	socket_info.socket = accept(init_sock, (struct sockaddr*)&(socket_info.client_addr), &(socket_info.client_length));
	socket_info.running = true;
}

Connection::~Connection(){
	//close socket
}

void Connection::run(){
	//create new thread to handle messaging
	pthread_attr_init(&thread_attrib);
	pthread_create(&thread_ID, &thread_attrib, Connection::connectionHandlingProcedures, (void*)&socket_info);
}

bool Connection::opened() const{
	return socket>=0;
}

bool Connection::finished() const{
	return !socket_info.running;
}





/*entry of thread execution*/
void* Connection::connectionHandlingProcedures(void* arg){
	bool running = true;
	SocketInfo& socket_info = *((SocketInfo*)arg);
	ServerUtil::log(ServerUtil::INFO, "Connection established!\n");

	while(socket_info.running){
		//read first messages (type of action) from client
		char _action[256];
		ssize_t N = read(socket_info.socket, _action, 255);
		if(N>=0){
			std::string action(_action);
			//do different things according to action
			if(action=="write"){
				ServerUtil::log(ServerUtil::INFO, "Reading from client\n");
				action_ReadFromClient(socket_info.socket);
			}else if(action=="print"){
				ServerUtil::log(ServerUtil::INFO, "Printing to client\n");
				action_PrintToClient(socket_info.socket);
			}else{
				ServerUtil::log(ServerUtil::ERROR, "Unsupported action!\n");
				socket_info.running = false;
			}
		}else{
			ServerUtil::log(ServerUtil::ERROR, "Failed to read client's action!\n");
		}
	}

	pthread_exit(nullptr);

}

void Connection::action_ReadFromClient(int socket){
	char data[256];
	ssize_t N = read(socket, data, 255);
	if(N>=0){
		std::string msg(data);
		ServerUtil::msg_pool.push_back(msg);
		ServerUtil::log(ServerUtil::INFO, "Read message successful\n");
	}else{
		ServerUtil::log(ServerUtil::ERROR, "Failed to read from client!\n");
	}
}

void Connection::action_PrintToClient(int socket){
	//do stuff
	//pour data from vector into string, each entry seperated by '\n'
	//char data[512];
	std::string data("");
	for(std::vector<std::string>::iterator iter=ServerUtil::msg_pool.begin(); iter!=ServerUtil::msg_pool.end(); ++iter){
		std::string msg(*iter);
		data += msg+"\n";
	}
	write(socket, data.c_str(), 19);
}
