#include "database.h"
#include "cache.h"

#include <vector>
#include <string>

#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

namespace ServerUtil{
	//log related util
	enum LogType{INSTRUCTION, PROMPT, ERROR, INFO};
	extern void log(LogType, const char*);

	//some other shit
	//extern std::vector<std::string> msg_pool;

	//database and cache
	extern Database db;
	extern Cache cache;

	extern void store(const char*);
	extern void fetch(const char*);
	extern std::string print();
};

#endif
