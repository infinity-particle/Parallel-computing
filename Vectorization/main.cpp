#include "matrix.h"

using namespace std;

int main(){
	Matrix A(2,2);
	system("clear");
	cin >> A;
	cout << A << endl;

	cout << A[0][1] << endl;

	return 0;
}
