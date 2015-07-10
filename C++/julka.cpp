#include <iostream>

using namespace std;

void writeOut(int* x, size_t l) {
	bool allzero = true;
	size_t k = l;
	while(x[k] == 0) k--;
	for(int i = k; i >= 0; i--) {
		if(x[i] != 0) allzero = false;
		cout << x[i];
	}
	if(allzero) cout << 0;
	cout << endl;
}

void divideByTwo(int* x, size_t &l) {
	int t = 0;
	for(unsigned int i = 0; i < l; i++){
		if(x[i]%2 == 0) x[i] /= 2;
		else { 
			int j = 0;
			t = x[i];
			while(t%2 != 0) {
				j++;
				t = t*10 + x[i+j];
			}
			t /= 2;
			for(int k = j; k >= 0; k--) {
				x[i+k] = t%10;
				t /= 10;
			}
			i += j;
		}
	}
}

int addArrays(int* x, int* y, int* sum, size_t lx, size_t ly) {
	int carry,i,j,k;
	carry = 0;
	for(i = lx, j = ly, k = -1; i >= 0 && j >= 0; i--, j--, k++) {
		sum[k] = (x[i] + y[j] + carry)%10;
		carry = (x[i] + y[j] + carry)/10;
	}
	if(lx > ly) {
		while(i >= 0) {
			sum[k++] = (x[i] + carry)%10;
			carry = (x[i--] + carry)/10;
		}
	} else if(lx < ly) {
		while(j >= 0) {
			sum[k++] = (y[j] + carry)%10;
			carry = (y[j--] + carry)/10;
		}
	} else {
		if(carry > 0) sum[k++] = carry;
	}
	return k;
}

int subtractArrays(int* x, int* y, int* sum, size_t lx, size_t ly) {
	int carry,i,j,k;
	carry = 0;
	i = lx-1; j = ly-1; k = 0;
	for(; i >= 0 && j >= 0; i--, j--, k++) {
		sum[k] = (x[i] - y[j] + carry)%10;
		if(sum[k] < 0) sum[k] += 10;
		carry = (x[i] - y[j] - 9 + carry)/10;
	}
	if(lx > ly) {
		while(i >= 0) {
			sum[k++] = (x[i] - 10 + carry)%10;
			if(sum[k-1] < 0) sum[k-1] += 10;
			carry = (x[i--] - 9 + carry)/10;
		}
	} else if(lx < ly) {
		while(j >= 0) {
			sum[k++] = (-y[j] + carry)%10;
			if(sum[k-1] < 0) sum[k-1] += 10;
			carry = (-y[j--] - 9 + carry)/10;
		}
	} else {
		if(carry > 0) sum[k++] = carry;
	}
	return k;
}

int main() {
	char xs[100];
	char ys[100];
	int x[100];
	int y[100];
	int sum[100];
	size_t lx, ly, ls;
	for(int w = 0; w < 10; w++) {
		for(int i = 0; i <= 100; i++) {
			xs[i] = 0; ys[i] = 0;
			x[i] = 0; y[i] = 0;
			sum[i] = 0;
		}
		cin >> xs >> ys;
		for(lx = 0; xs[lx] != '\0'; lx++) x[lx] = xs[lx] - '0';
		for(ly = 0; ys[ly] != '\0'; ly++) y[ly] = ys[ly] - '0';
		divideByTwo(x, lx); divideByTwo(y, ly);
		ls = addArrays(x, y, sum, lx, ly);
		writeOut(sum, ls);
		for(int i = 0; i <= 100; i++) sum[i] = 0;
		ls = subtractArrays(x, y, sum, lx, ly);
		writeOut(sum, ls);
	}
	return 0;
}
