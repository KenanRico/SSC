
#include <vector>
#include <string>

#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

namespace ServerUtil{
	//log related util
	enum LogType{INSTRUCTION, PROMPT, ERROR, INFO};
	extern void log(LogType, const char*);

	//some other shit
	extern std::vector<std::string> msg_pool;
};

#endif
