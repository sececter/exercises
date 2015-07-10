#include <iostream> 

using namespace std;

int main() 
{ 
	double i, j; 
	cout<<"\n\tEnter numerator : "; 
	cin>>i; 
	cout<<"\n\tEnter denominator : "; 
	cin>>j; 
    
    try {
        if(j != 0) cout << "Result: " << i/j;
        else throw "Exception: 0";
    } catch (const char* msg) {
        cout << msg << endl;
    }
    
    return 0;  
}
  
