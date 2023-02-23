#ifndef TP3_COPIABLE_H
#define TP3_COPIABLE_H

using namespace std;

class Copiable {
public : 
	virtual Copiable* copie() const = 0;
};

#endif