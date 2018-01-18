#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <string>
#include <pthread.h>


#ifndef CONNECTION_H
#define CONNECTION_H

class Connection{
	private:
		typedef struct _SocketInfo{
			struct sockaddr_in client_addr;
			socklen_t client_length;
			int socket;		
			bool running;
		} SocketInfo;
	private:
		//socket related members
		SocketInfo socket_info;
		//thread related memebers
		pthread_t thread_ID;
		pthread_attr_t thread_attrib;

	public:
		Connection(int);
		~Connection();
	private:
		Connection() = delete;
		Connection(const Connection&) = delete;
		Connection& operator=(const Connection&) = delete;

	public:
		bool opened() const;
		bool finished() const;
		void run();
	private:
		static void* connectionHandlingProcedures(void* arg);
};

#endif
