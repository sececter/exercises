// this code contains errors
// [search and replace a word in a text file]
#include<iostream>
#include<fstream>
#include<string>
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
    if (s == argv[2]) {
      cout << argv[3];
    } else {
      cout << s;
    }
    cout << " ";
  }
  cout << endl;
  ifs.close();
  return 0;
}
