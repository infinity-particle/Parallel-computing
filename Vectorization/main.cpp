#include "matrix.h"

using namespace std;

int main(){
	Matrix A(2,2), B;
	system("clear");
	cin >> A;

	B = A;

	cout << B;

	cout << B(0,1) << endl;

	return 0;
}
