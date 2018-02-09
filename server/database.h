
#include <string>
#include <fstream>


#ifndef DATABASE_H
#define DATABASE_H

class Database{
	private:
		std::string path;

	public:
		Database(const char*);
		~Database();
	private:
		Database() = delete;
		Database(const Database&) = delete;
		Database& operator=(const Database&) = delete;

	public:
		bool found(const char*) const;
		void insert(const char*);
		std::string print() const;
};

#endif
