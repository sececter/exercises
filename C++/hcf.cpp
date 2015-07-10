#include <iostream>    
#include <string>    
using namespace std;    
    
int main()    
{    
	int dividend, divisor, hcf,max,i;    
	   
        cout<<"Enter two numbers : ";    
        cin>>dividend>>divisor;    
    
            if (dividend > divisor) max = dividend;
            else max = divisor;
            
            i = 1;
            while(i < max) {
                if(dividend % i == 0 && divisor % i == 0) {
                    hcf = i;
                }
                i++;
            }
             
             cout<<hcf;    
            
 	return 0;    
}   
    

