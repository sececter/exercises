#include <iostream>

using namespace std;

typedef char prvek_t;

typedef struct {
	prvek_t* prvky;
	int vrchol;
} zasob_t;

void zasob_init(zasob_t* zasob, int velikost)
{
	prvek_t* novy = new prvek_t[velikost];
	zasob->prvky = novy;
	zasob->vrchol = -1;
}

void zasob_vloz(zasob_t* zasob, prvek_t prvek)
{
	zasob->prvky[++zasob->vrchol] = prvek;
}

prvek_t zasob_vyjmi(zasob_t* zasob)
{
	return zasob->prvky[zasob->vrchol--];
}

bool zasob_prazdny(zasob_t* zasob)
{
	return zasob->vrchol < 0;
}

void zasob_smaz(zasob_t* zasob)
{
	zasob->vrchol = -1;
	zasob->prvky = NULL;
	delete(zasob->prvky);
}

void print_dec_to_hex(int dec_input) 
{
	char hex_digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	zasob_t hex_output;
	zasob_init(&hex_output, 256);
	while(dec_input > 0)
	{
		zasob_vloz(&hex_output, hex_digits[dec_input % 16]);
		dec_input /= 16;
	}
	while(!zasob_prazdny(&hex_output))
	{
		cout << zasob_vyjmi(&hex_output);
	}
	cout << endl;
	zasob_smaz(&hex_output);
}		
	

int main() 
{
	
	while(true)
	{
		int dec_input = 0;
		
		cout << "Zadejte cislo v desitkove soustave (1 - 4 294 967 295), ktere si prejete prevest do sestnactkove soustavy, 0 pro ukonceni: ";
		cin >> dec_input;
		if(dec_input > 0)
			print_dec_to_hex(dec_input);
		else return 0;
	}
	
	return 0;
}
