#include "serverutil.h"
#include "database.h"
#include "cache.h"

#include <iostream>
#include <string>

namespace ServerUtil{
	void log(LogType type, const char* msg){
		std::cout<<msg;
	}

	//std::vector<std::string> msg_pool;

	Database db("Database/file.txt");

	Cache cache(10);

	void store(const char* entry){
		if(cache.found(entry)){
			log(ERROR, "entry already exists!");
		}else{
			if(db.found(entry)){
				log(ERROR, "entry already exists!");
			}else{
				log(INFO, "Inserting entry into cache and database!");
				db.insert(entry);
				cache.insert(entry);
			}
		}
	}

	void fetch(const char* entry){
		if(cache.found(entry)){
			log(INFO, "Found entry in cache!");
		}else{
			if(db.found(entry)){
				log(INFO, "Found entry in database!");
			}else{
				log(INFO, "Entry does not exist!");
			}
		}
	}

	std::string print(){
		return db.print();
	}
}
