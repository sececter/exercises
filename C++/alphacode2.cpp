#include <string>
#include <map>
#include <iostream>

using namespace std;

int ways(std::string s) {
  static map<string,int> cache;
  map<string,int>::const_iterator f = cache.find(s);
  if (f!=cache.end()) return f->second;
  if (s.size()==0) {
	  //cache.insert({s,1});
	  return 1;
  }
  if (s[0]=='0'){
	  //cache.insert({s,1});
      return 0; // no way the first digit is 0   
  }                                                                                  
  if (s.size()==1) {
	  //cache.insert({s,0});
	  return 1; // only one possibility for a single digit  
  }                                                                     
  // here we have at least 2 digits                                                                                                           
  int n = 10*(s[0]-'0')+(s[1]-'0');
  if (n>26) {
	  int ret = ways(s.substr(1));
	  cache.insert(pair<string,int>(s,ret));
	  return ret; // cannot merge first two digits.
  }
  int ret = ways(s.substr(1)) + ways(s.substr(2));
  cache.insert(pair<string,int>(s,ret));                                                                  
  return ret; // two possible interpretations                                                               
}

int main() {
  string s;
  while(cin >> s, s.at(0) != '0') cout << ways(s) << endl;
  return 0;
}
