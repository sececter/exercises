struct Stav { Vez *l, *s, *p; };

class Hra {
public:
	Hra(int N);
	void vykresli(int krok);
private:
	int N;
	Vez *l, *s, *p;
	Stav* stavy;
	void presun(Vez *z, Vez *na, int krok);
	void vyres();
};
