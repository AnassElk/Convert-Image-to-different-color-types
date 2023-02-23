#ifndef TP4_LIBRAIRIE_H
#define TP4_LIBRAIRIE_H

#include "Image.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <iostream>
#include "Affichable.h"
#include "Foncteurs.h"

using namespace std;

class Librairie: public Affichable
{
public:
	Librairie(const std::string& nom);
	Librairie(const Librairie& librairie);
	Librairie& operator=(const Librairie& librairie);

	std::string getNom() const;
	size_t getNombreImages() const;
	void setNom(const std::string nom);
	
    //TODO
    template<typename T>
	void ajouterImage(const std::string& nomImage);
	Librairie& operator-=(const std::string& id);
	Image* operator[](const std::string& id);

	void modifierNomImage(const std::string& id, const std::string& nom);
	void supprimerTout();

	///TODO
	const Image* getImagesParNom(const std::string& nomImage);

    template<typename Comparateur = ComparateurNom>
    std::set <const Image*, Comparateur> getImagesParNomPartiel(const std::string& nomImage);
    
	template<typename Comparateur = ComparateurId>
	std::set<const Image*, Comparateur> getImagesParTailles(int tailleDebut, int tailleFin);
    
	template<typename Comparateur = ComparateurId>
	std::set<const Image*, Comparateur> getImagesParTaille(int taille);

    template<typename Comparateur = ComparateurId>
    std::set<const Image*, Comparateur> getImagesTrier();

private:
	void afficher(std::ostream& sortie) const override;

	std::unordered_map<std::string, std::unique_ptr<Image>> images_;
	std::unordered_map<std::string, const Image*> filtreNomImage_;
	std::map<int, std::vector<const Image*>> filtreTaille_;
	std::string nomLibrairie_;
};

template<typename T>
void Librairie::ajouterImage(const std::string& nomImage) {
	if (filtreNomImage_.find(nomImage) == filtreNomImage_.end()) {
		unique_ptr<Image> image = make_unique<T>(nomImage, nomLibrairie_);
		image->load();
		filtreNomImage_[nomImage] = image.get();
		vector<const Image*> vect;
		vect.push_back(image.get());
		filtreTaille_[image->getTaille()] = vect;
		images_[image->getId()] = move(image);
	}
}

template<typename Comparateur>
std::set <const Image*, Comparateur> Librairie::getImagesParNomPartiel(const std::string& nomImage){
	set<const Image*, Comparateur> result;
	for (auto&& [cle, image] : filtreNomImage_) {
		if (cle.find(nomImage) != string::npos) {
			result.insert(image);
		}
	}
	return result;
}

template<typename Comparateur>
std::set<const Image*, Comparateur> Librairie::getImagesParTailles(int tailleDebut, int tailleFin) {

	auto [debut, fin] = std::equal_range(filtreTaille_.begin(), filtreTaille_.end(), 0, ImageEstDansIntervalleTailles(tailleDebut, tailleFin));

	set<const Image*, Comparateur> result;
	while (debut != fin) {
		copy(debut->second.begin(), debut->second.end(), inserter(result, result.end()));
		debut++;
	}
	return result;
}

template<typename Comparateur>
std::set<const Image*, Comparateur> Librairie::getImagesParTaille(int taille) {
	return getImagesParTailles(taille, INT_MAX);
}

template<typename Comparateur>
std::set<const Image*, Comparateur> Librairie::getImagesTrier() {
	set<const Image*, Comparateur> result;
	transform(images_.begin(), images_.end(), inserter(result, result.end()), [](const auto& c) {return c.second.get(); });
		return result;
}

#endif
