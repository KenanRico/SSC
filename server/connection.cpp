#include "connection.h"
#include "serverutil.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <vector>
#include <string>


Connection::Connection(int init_sock){ //no constructor cuz don't know how to init client_addr lol
	socket_info.client_length = sizeof(socket_info.client_addr);
	socket_info.socket = accept(init_sock, (struct sockaddr*)&(socket_info.client_addr), &(socket_info.client_length));
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

/*entry of thread execution*/
void* Connection::connectionHandlingProcedures(void* arg){
	SocketInfo& socket_info = *((SocketInfo*)arg);
	ServerUtil::log(ServerUtil::INFO, "Connection established!\n");


	pthread_exit(nullptr);
}
