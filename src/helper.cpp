#include "helper.hpp"

#include <list>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <algorithm>

std::vector<int> randompermutation(int size){
	std::vector<int> ret(size);
	std::iota(ret.begin(),ret.end(),1);
	return ret;
}

std::queue<int> randompermutationQ(int size){
	std::queue<int> ret;
	for(int i:randompermutation(size))ret.push(i);
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
