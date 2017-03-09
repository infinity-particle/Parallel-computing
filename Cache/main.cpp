#include "array.h"

#define BLOCK_SIZE 65536
#define OFFSET 1048576
#define N 4
#define NUMBER_OF_ITERATIONS 15

//unsigned long long rdtsc();

int main(){

	Array array(BLOCK_SIZE, N, OFFSET);
	//Array array(32, 4, 64);
	//array.fillWithZigzagIndex();

	//std::cout << array << std::endl;

	return 0;
}

/*unsigned long long rdtsc(){
    unsigned int low,high;
    __asm__ __volatile__ ("rdtsc" : "=a" (low), "=d" (high));
    return ((unsigned long long)high << 32) | low;
}*/