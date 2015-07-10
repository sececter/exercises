class Vez {
public:
	Vez(int N);
	~Vez();
	bool prazdna();
	bool plna();
	int vyjmi();
	void vloz(int disk);
	int operator[](int i);
private:
	int vrch;
	int* disky;
	int kapacita;
};
