
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstring>
#include <climits>


void getServerInfo(std::string&, int&);
void getServerInfo(struct hostent*&, struct sockaddr_in&, const std::string&, int);
bool connectToServer(int, struct sockaddr_in&);
void writeInput(int);


int main(){
	//open socket
	int main_socket = socket(AF_INET, SOCK_STREAM, 0);

	//declare and specify server info (address, port)
	std::string server_name = "";
	int port = 0;
	getServerInfo(server_name, port);

	//declare and specify more server info
	struct hostent* server = nullptr;
	struct sockaddr_in serv_addr;
	getServerInfo(server, serv_addr, server_name, port);

	//connect to server and do stuff
	if(connectToServer(main_socket, serv_addr)){
		//do some actions
		writeInput(main_socket);
	}else{
		std::cout<<"Failed to connect to server!\n";
	}
	
	
	return 0;
}


void getServerInfo(std::string& server_name, int& port){
	std::cout<<"Address of server: ";
	std::cin>>server_name;
	std::cout<<"Port number: ";
	std::cin>>port;
}

void getServerInfo(struct hostent*& server, struct sockaddr_in& serv_addr, const std::string& server_name, int port){
	server = gethostbyname(server_name.c_str());
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);
}

bool connectToServer(int main_socket, struct sockaddr_in& serv_addr){
	return (connect(main_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr))>=0);
}

void writeInput(int socket){
	std::cout<<"Please specify a message to write to server:\n";
	std::string msg("");
	//get user input
	std::cin>>msg;
	write(socket, msg.c_str(), 255);
}
