#include "helper.hpp"

#include <list>
#include <cstdlib>
#include <ctime>
#include <cstdio>

std::vector<int> randompermutation(int size){
	std::vector<int> ret(size, 0);
	std::list<int> tmp;
	std::list<int>::iterator it;

	for(int i = 0; i < size; i++)
		tmp.push_back(i);

	srand(time(NULL));
	for(int i = 0; i < size; i++){
		int id = rand() % int(tmp.size());

		it = tmp.begin();
		while(id--) it++;

		ret[i] = *it;

		tmp.erase(it);
	}

	return ret;
}

int readIntInRange(int L, int R){
	int ret;
	scanf("%d", &ret);
	while(ret < L || ret > R){
		printf("Input invalido.\n");
		scanf("%d", &ret);
	}
	return ret;
}

bool isAlphaNumerical(char c){
	return (c >= 'A' && c <= 'Z') ||
		   (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

char readchar(){
	char ret;
	ret = getchar();
	while(!isAlphaNumerical(ret)) ret = getchar();

	return ret;
}
