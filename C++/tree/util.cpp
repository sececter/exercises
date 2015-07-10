#ifndef _UTILCPP
#define _UTILCPP
#include <string>
#include "bin_strom.h"

using namespace std;

bool je_cislo(string s) {
	unsigned short i;
	for(i = 0; i < s.length(); i++)
		if(!isdigit(s[i])) break;
	return !s.empty() && i == s.length();	
}

inline bool je_list(uzel* u) {
	return u->levy == NULL && u->pravy == NULL;
}

inline bool je_ve_vetvi(uzel* u) {
	return !je_list(u) && (u->levy == NULL || u->pravy == NULL);
}

inline bool je_levym_naslednikem(uzel* u, uzel* rodic) {
	return rodic->levy == u;
}
#endif
