#include <iostream>
#include <string>

using namespace std;

bool error;

string transformIntoJava(string& s) {
	string::iterator it = s.begin();
	while(it++ != s.end()) {
		if(*it == '_') {
			s.erase(it, it+1);
			*it = toupper(*it);
		}
	}
	return s;
}

string transformIntoCpp(string& s) {
	string::iterator it = s.begin();
	while(it++ != s.end()) {
		if(isupper(*it)) {
			*it = tolower(*it);
			it = s.insert(it,'_');
		}
	}
	return s;
}

bool isValidCpp(string& s) {
	bool ret = true;
	bool foundAnUpper = false;
	string::iterator it;
	for(it = s.begin(); it != s.end(); it++) {
		if(isspace(*it) || 
			(*it == '_' && *(it+1) == '_') ||
			(*it == '_' && it == s.end()-1)) { 
				error = true; 
				ret = false;
				return ret;
		}
		if(isupper(*it)) {
			foundAnUpper = true;
			ret = false; 
		}
	}
	size_t pos = s.find('_');
	while(pos != string::npos) {
		if(pos == 0 || pos == string::npos || foundAnUpper) {
			error = true;
			ret = false;
			break;
		}
		else if(s[pos+1] != '_') ret = true;
		pos = s.find('_',pos+1);
	}
	return ret;
}

bool isValidJava(string& s) {
	bool isThereAnUpper = false;
	bool ret = true;
	string::iterator it = s.begin();
	if(isupper(*it)){
		error = true;
		ret = false;
	}
	for(; it != s.end() && ret != false; it++) {
		if(isspace(*it)) {
			error = true;
			ret = false;
		}
		if(*it == '_') ret = false;
		if(isupper(*it)) isThereAnUpper = true;
	}
	if(isThereAnUpper && ret != false) ret = true;
	return ret;
}

int main() {
	string s;
	while(getline(cin,s)) {
		error = false;
		if(isValidCpp(s)) s = transformIntoJava(s);
		else if(isValidJava(s)) s = transformIntoCpp(s);
		else if(error) s = "Error!";
		cout << s << endl;
	}
	return 0;
}

