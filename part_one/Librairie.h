#ifndef TP3_LIBRAIRIE_H
#define TP3_LIBRAIRIE_H

#include "Image.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Librairie : public Affichable
{
public:
	Librairie(const std::string& nom);
	Librairie(const Librairie& librairie);
	Librairie& operator=(const Librairie& librairie);

	std::string getNom() const;
	size_t getNombreImages() const;
	void setNom(const std::string nom);

	Librairie& operator+=(const std::string& nomImage);
	Librairie& operator-=(const std::string& nomImage);
	Image* operator[](const std::string&);
	void supprimerTout();



private:
	int trouverIndexImage(const std::string&) const;
	void afficher(std::ostream& sortie) const override;

	std::vector<std::unique_ptr<Image>> images_;
	std::string nomLibrairie_;
};


#endif