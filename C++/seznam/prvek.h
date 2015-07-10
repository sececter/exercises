class prvek
{
	public:
		prvek(int d = 0);
		void UlozHodnotu(int d);
		int Hodnota();
		void UlozDalsi(prvek* p);
		prvek *Dalsi();
	private:
		int data;
		prvek* dalsi;
};

