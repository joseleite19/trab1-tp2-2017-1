#include <cstdio>
#include "helper.hpp"

int main(){
	std::vector<int> ret = randompermutation(10);

	for(int i = 0; i < 10; i++)
		printf(" %d", ret[i]);
	printf("\n");



	return 0;
}