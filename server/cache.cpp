#include "cache.h"

#include <string>


Cache::Cache(int s): size(s), cache(new std::string[s]()), counter(new int[s]()){
	//init cache anc counter
	for(int i=0; i<size; ++i){
		counter[i] = 0;
		cache[i] = "";
	}
}

Cache::~Cache(){
	delete[] cache;
	delete[] counter;
}


bool Cache::found(const char* e) const{
	bool result = false;
	std::string entry(e);
	for(int i=0; i<size; ++i){
		if(cache[i]==entry){
			result = true;
			break;
		}else;
	}
}

void Cache::insert(const char* e){
	std::string entry(e);

	//run caching algorithm to choose an entry to evict
	int index = evict();

	//replace selected entry in cache
	if(index>=0){
		cache[index] = entry;
		counter[index] = 0;
	}else;
}

int Cache::evict(){
	int max = 0;
	int index = -1;

	//find index to remove
	for(int i=0; i<size; ++i){
		if(counter[i]>max){
			max = counter[i];
			index = i;
		}else;
	}

	//remove entry in cache and counter
	if(index>=0){
		cache[index] = "";
		counter[index] = -1;
	}else;

	return index;
}
