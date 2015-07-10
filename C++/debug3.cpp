#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	using namespace std;
	ifstream ifs(argv[0]);
	char c;
	int characters = 0;
	int printables = 0;
	while(true) {
		ifs.get(c);
		if (ifs.eof()) break;
		characters++;
		if (isalnum(c) || ispunct(c) || isspace(c)) printables++;
	}
	ifs.close();
	cout << "filesize: " << characters << " bytes, characters: " << printables << endl;
	return 0;
}
