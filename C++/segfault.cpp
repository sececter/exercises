#include<iostream>
int main(int argc, char** argv) {
	using namespace std;
	double* d = new double[3];
	for(unsigned int i = 0; i < 3; i++) {
		d[i] = 1.5 + i;
	}
	for(unsigned int i = 2; i >= 0; i--) {
		cout << d[i] << endl;
	}
}
