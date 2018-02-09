#include "database.h"
#include "serverutil.h"

#include <string>
#include <fstream>
#include <cstring>
#include <iostream>


Database::Database(const char* p): path(p){

}

Database::~Database(){

}


bool Database::found(const char* ent) const{
	std::fstream file_in(path.c_str(), std::ios::in);
	bool result = false;
	if(file_in.is_open()){
		//read file line by line
		std::string entry(ent);
		std::string line("");
		while(file_in>>line){
			if(entry==line){
				result = true;
			}else;
		}
	}else{
		ServerUtil::log(ServerUtil::ERROR, "No file open for database!");
	}
	file_in.close();
	return result;
}

void Database::insert(const char* ent){
	std::fstream file_out(path.c_str(), std::ios::out|std::ios::app);
	if(file_out.is_open()){
		//append entry to end of file
		std::string entry(ent);
		file_out<<entry<<" ";
	}else{
		ServerUtil::log(ServerUtil::ERROR, "No file open for database!");
	}
	file_out.close();
}

std::string Database::print() const{
	std::fstream file_in(path.c_str(), std::ios::in);
	std::string result("");
	std::string s("");
	while(file_in>>s){
		std::cout<<s<<"\n";
		result += s;
	}
	file_in.close();
	return result;
}
