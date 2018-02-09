//LFU caching

#include <string>


#ifndef CACHE_H
#define CACHE_H

class Cache{
	private:
		int size;
		std::string* cache;
		int* counter;

	public:
		Cache(int);
		~Cache();
	private:
		Cache() = delete;
		Cache(const Cache&) = delete;
		Cache& operator=(const Cache&) = delete;
		
	public:
		bool found(const char*) const;
		void insert(const char*);
	private:
		int evict();
};

#endif
