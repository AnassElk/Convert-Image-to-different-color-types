#ifndef TP3_AFFICHABLE_H
#define TP3_AFFICHABLE_H

#include<iostream>
using namespace std;

class Affichable {
public: 
	virtual void afficher(ostream& sortie) const = 0;
	friend ostream& operator<<(ostream& sortie, Affichable& affichable) {
		affichable.afficher(sortie);
		return sortie;
	}
};

#endif