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
	SocketInfo& socket_info = *((SocketInfo*)arg);
	ServerUtil::log(ServerUtil::INFO, "Connection established!\n");
	//read data from socket
	char data[256];
	ssize_t N = read(socket_info.socket, data, 255);
	if(N>=0){
		std::string msg(data);
		ServerUtil::log(ServerUtil::INFO, "Read message successful\n");
	}else{
		ServerUtil::log(ServerUtil::ERROR, "Failed to read from client!\n");
	}
	socket_info.running = false;
	pthread_exit(nullptr);
}
