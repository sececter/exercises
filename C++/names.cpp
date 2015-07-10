#include <iostream>
#include <string>

using namespace std;

string transformIntoJava(string s) {
	string ret = s;
	string::iterator it = ret.begin();
	while(it++ != ret.end()) {
		if(*it == '_') {
			ret.erase(it, it+1);
			*it = toupper(*it);
		}
	}
	return ret;
}

string transformIntoCpp(string s) {
	string ret = s;
	string::iterator it = ret.begin();
	while(it++ != ret.end()) {
		if(isupper(*it)) {
			*it = tolower(*it);
			it = ret.insert(it,'_');
		}
	}
	return ret;
}

bool isValidCpp(string s) {
	string::iterator it;
	for(it = s.begin(); it != s.end(); it++) {
		if(isupper(*it) || isspace(*it)) return false;
	}
	size_t pos = s.find('_');
	if(pos == 0) return false;
	if(pos == string::npos) return false;
	else if(s[pos+1] != '_') return true;
	return false;
}

bool isValidJava(string s) {
	bool isThereAnUpper = false;
	string::iterator it = s.begin();
	if(isupper(*it)) return false;
	for(; it != s.end(); it++) {
		if(isspace(*it) || *it == '_') return false;
		if(isupper(*it)) isThereAnUpper = true;
	}
	if(isThereAnUpper) return true;
	else return false;
}

int main() {
	string s;
	while(cin >> s, s != "") {
		if(isValidCpp(s)) s = transformIntoJava(s);
		else if(isValidJava(s)) s = transformIntoCpp(s);
		else s = "Error!";
		cout << s << endl;
	}
	return 0;
}
