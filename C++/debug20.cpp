// [search and replace a word in a text file]
#include<iostream>
#include<fstream>
#include<string>

void replaceInString(std::string& s, std::string needle, std::string replace) {
	for (int i = 0; i < s.length(); i++) {
		if (s.substr(i, needle.length()) == needle) {
			s.replace(i,needle.length(), replace, 0, replace.length());
		}
	}
}

int main(int argc, char** argv) {
  using namespace std;
  if (argc < 4) {
    cout << "need a filename, a word and its replacement on cmd line" << endl;
    return 1;
  }
  ifstream ifs(argv[1]);
  if (!ifs) {
    cout << "cannot open file " << argv[1] << endl;
    return 2;
  }
  string s;
  while(!ifs.eof()) {
    ifs >> s;
    if (ifs.eof()) {
      break;
    }
    replaceInString(s, argv[2], argv[3]);
    cout << s;
    cout << " ";
  }
  cout << endl;
  ifs.close();
  return 0;
}
