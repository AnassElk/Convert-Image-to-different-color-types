#ifndef TP4_AFFICHABLE_H
#define TP4_AFFICHABLE_H

#include <iostream>

class Affichable {
public:
	virtual ~Affichable() = default;
	friend std::ostream& operator<<(std::ostream& out, const Affichable& affichable) {
		affichable.afficher(out);
		return out;
	}

private:
	virtual void afficher(std::ostream& out) const = 0;
};

#endif