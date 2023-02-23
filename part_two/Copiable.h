#ifndef TP4_COPIABLE_H
#define TP4_COPIABLE_H

class Copiable {
public:
	virtual ~Copiable() = default;
	virtual Copiable* copie() const = 0;
};

#endif