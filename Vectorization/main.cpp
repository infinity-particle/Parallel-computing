#include "hypermatrix.h"

using namespace std;

int main(){
	Hypermatrix A(8,8,4,4), B(8,8,4,4), result;
	A.fillRandom(2048);
	B.fillRandom(2048);
	
	result = A * B;

	cout << "Result of A * B:" << endl;
	cout << result << endl;


	return 0;
}
