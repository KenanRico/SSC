#include "serverutil.h"

#include <iostream>

namespace ServerUtil{
	void log(LogType type, const char* msg){
		std::cout<<msg;
	}
	std::vector<std::string> msg_pool;
}
