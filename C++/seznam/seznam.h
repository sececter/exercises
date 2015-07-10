#include "prvek.cpp"
class seznam
{
	public:
		seznam();
		~seznam();
		prvek* vlozNaKonec(int d);
		prvek* vlozZa(prvek* p, int d);
		prvek* najdi(int d, prvek* prvek);
		void vyjmi(int d);
		int vyjmiPrvni();
		void vyprazdni();
	
	private:
		prvek* hlava;
		prvek* zarazka;
};
