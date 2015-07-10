#ifndef _BINSTROMH
#define _BINSTROMH

typedef char* data_t;

struct uzel {
	uzel();
	uzel(data_t hodnota);
	~uzel();
	data_t hodnota;
	uzel *levy;
	uzel *pravy;	
};

struct bstrom {
	public:
		bstrom();
		bstrom(char* jmeno_souboru);
		~bstrom();
		
		void vloz_uzel(data_t hodnota);
		bool smaz_uzel(data_t hodnota);
		uzel* najdi_uzel(data_t hodnota, uzel* tento_uzel, uzel* uzel_predchudce);
		
		void vyska_stromu();
		
		void vytiskni_strom();
		
		uzel* vrat_koren();
	
	private:
		uzel* koren;
				
		void vloz_uzel_r(uzel* u, data_t &hodnota);
		
		void smaz_list(uzel* u, uzel* predchudce);
		void smaz_ve_vetvi(uzel*u, uzel* predchudce);
		
		void zpracuj_inorder(uzel* u, void (*F)(uzel*));
		void zpracuj_preorder(uzel* u, void (*F)(uzel*));
		void zpracuj_postorder(uzel* u, void (*F)(uzel*));
		
		void znic_podstrom(uzel* u);
};
		
#endif
