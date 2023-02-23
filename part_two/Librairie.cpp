#include "Librairie.h"
#include "ImageRGB.h"
#include <unordered_map>

using namespace std;

Librairie::Librairie(const std::string& nom) : nomLibrairie_(nom)
{
}

Librairie::Librairie(const Librairie& librairie)
{
	*this = librairie;
}

/*TODO: Mettre à jour la méthode mkki*/
Librairie& Librairie::operator=(const Librairie& librairie)
{
	nomLibrairie_ = librairie.nomLibrairie_;
	supprimerTout();

	for (const auto& image : librairie.images_) {
		images_.insert({ image.second->getNom(),  unique_ptr<Image>(dynamic_cast<Image*>(image.second->copie())) });
	}

	return *this;
}

std::string Librairie::getNom() const { return nomLibrairie_; }
size_t Librairie::getNombreImages() const { return images_.size(); }

/*TODO: Mettre à jour la méthode*/
void Librairie::setNom(const std::string nom) 
{
	nomLibrairie_ = nom;
	for (auto& image : images_) {
		image.second->setDossier(nomLibrairie_);
	}
}

/*TODO: Mettre à jour la méthode*/
Librairie& Librairie::operator-=(const std::string& id) 
{
	auto it = images_.find(id);
	if (it != images_.end()) {
		const Image* imageASupprimer = getImagesParNom(it->second->getNom());
		// supprimer l image du conteneur filtrNomImage_
		auto it1 = filtreNomImage_.find(imageASupprimer->getNom());
		filtreNomImage_.erase(it1);
		// supprimer l image du conteneur filtreTaille_
		auto it2 = filtreTaille_.find(imageASupprimer->getTaille());
		for (int i = 0; i <= it2->second.size(); i++) {
			if (it2->second[i] == imageASupprimer) {
				it2->second.erase(it2->second.begin() + i);
			}
		}
		// supprimer l image du conteneur images_
		images_.erase(it);
	}
	return *this;
	/*const Image* image = getImagesParNom(nomImage);
	images_.erase(std::remove_if(images_.begin(), images_.end(), [nomImage, this] (const auto& it) {return it->first == nomImage; }));*/
	return *this;
}

/*TODO: Mettre à jour la méthode*/
Image* Librairie::operator[](const std::string& id) 
{
	auto it = images_.find(id);
	if (it != images_.end()) {
		return it->second.get();
	}
	else return nullptr;
	
	//int i = trouverIndexImage(nomImage);
	/*if (i == -1) {
		return nullptr;
	}
	else {
		return images_[i].get();
	}*/
}

void Librairie::modifierNomImage(const string& id, const string& nom) {
	//TODO: Implémenter la méthode
	auto it = images_.find(id);
	if (it != images_.end()) {
		it->second->setNom(nom);
	}

}

/*TODO: Mettre à jour la méthode*/
void Librairie::supprimerTout()
{
	images_.clear();
	filtreNomImage_.clear();
	filtreTaille_.clear();
}

/*TODO: Mettre à jour la méthode*/
void Librairie::afficher(std::ostream& sortie) const
{
	cout << "Nom librairie: " << nomLibrairie_ << endl;
	for (auto& image : images_) {
		sortie << *image.second << endl;
	}
}

const Image* Librairie::getImagesParNom(const std::string& nomImage) {
	auto it = filtreNomImage_.find(nomImage);
	if (it != filtreNomImage_.end()) {
		return it->second;
	}
	return nullptr;
}