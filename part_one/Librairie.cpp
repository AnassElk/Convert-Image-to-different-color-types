#include "Librairie.h"
#include "ImageRGB.h"

using namespace std;

Librairie::Librairie(const std::string& nom) : nomLibrairie_(nom)
{
}

Librairie::Librairie(const Librairie& librairie)
{
	*this = librairie;
}

Librairie& Librairie::operator=(const Librairie& librairie)
{
	if (&librairie != this) {
		nomLibrairie_ = librairie.nomLibrairie_;
		supprimerTout();

		for (auto& image : librairie.images_) {
			/*unique_ptr<Image> imageP;
			imageP = move(images_);*/
				images_.push_back(unique_ptr<Image>(dynamic_cast<Image*>(image -> copie())));

			}
		
		}
	

	return *this;
}

std::string Librairie::getNom() const { return nomLibrairie_; }
size_t Librairie::getNombreImages() const { return images_.size(); }

void Librairie::setNom(const std::string nom)
{
	nomLibrairie_ = nom;
	for (auto& image : images_) {
		image->setDossier(nomLibrairie_);
	}
}

Librairie& Librairie::operator+=(const std::string& nomImage)
{
	Image* image = (*this)[nomImage];
	if (image == nullptr) {
		images_.push_back(make_unique<ImageRGB>(nomImage, nomLibrairie_));
		images_.back()->load();
	}

	return *this;
}

Librairie& Librairie::operator-=(const std::string& nomImage)
{
	int i = trouverIndexImage(nomImage);
	if (i != -1) {
		images_[i] = move(images_.back());
		images_.pop_back();
	}

	return *this;
}

Image* Librairie::operator[](const std::string& nomImage)
{
	int i = trouverIndexImage(nomImage);
	if (i == -1) {
		return nullptr;
	}
	else {
		return images_[i].get();
	}
}

void Librairie::supprimerTout()
{
	images_.clear();
}

int Librairie::trouverIndexImage(const std::string& nomImage) const
{
	for (unsigned int i = 0; i < images_.size(); i++) {
		if (*images_[i] == nomImage) return i;
	}

	return -1;
}

void Librairie::afficher(std::ostream& sortie) const
{
	sortie << "Nom librairie: " << nomLibrairie_ << endl;
	for (auto& image : images_) {
		sortie << *image << endl;
	}
}