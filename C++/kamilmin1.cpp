#include <iostream>
#include <cmath>
using namespace std; int main(){for(int i=0;i<10;i++){char*w=new char[25];cin>>w;int j=0 , p=0;while(j<25){if(w[j]=='T'||w[j]=='D'||w[j]=='L'||w[j]=='F')p++;j++;}cout<<pow(2,p)<<endl;delete[]w;}return 0;}
