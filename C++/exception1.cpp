#include<iostream> 
using namespace std;

class fourException {
	public:
		static int w;
		fourException() { w++; }
};

int fourException::w = 0;

int main() 
{ 
	int num, count=0; 
	cout<<"\n\tEnter the number of iterations : "; 
	cin>>num; 
	for(int i=1;i<=num;i++) 
	{ 
		try {
			if(i % 4 == 0) throw fourException();
		} catch (fourException ex) {
			continue;
		}
    }
    count = fourException::w;
	cout<<"\n\tNumber of exceptions : "<<count; 
	return 0; 
}
