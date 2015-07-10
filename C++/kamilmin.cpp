#include<iostream>
#include<cmath>
using namespace std;int main(){char w[9][20];for(int i=0;i<10;i++){cin>>w[i];}for(int i=0;i<10;i++){int j=0 , p=0;while(j<21){char c=w[i][j];if(c=='T'||c=='D'||c=='L'||c=='F')p++;j++;}cout<<pow(2,p)<<endl;}return 0;}
