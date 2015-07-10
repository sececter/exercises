#include <iostream>
#include <string>
using namespace std;

class Napis
{
	public:
		Napis(string);
		Napis();
		~Napis();
		void vypis();
	private:
		string text;
};

Napis::Napis()
{
	text = "Nazdar!";
}
Napis::Napis(string s)
{
	text = s;
}

Napis::~Napis() { }

void Napis::vypis()
{
	cout << text << endl;
}

Napis blabol(string("Dalsi text"));

int main()
{
	blabol.vypis();
	return 0;
}
