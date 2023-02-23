#ifndef TP4_IMAGE_H
#define TP4_IMAGE_H

#include "Pixel.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Copiable.h"
#include "Affichable.h"

class Image: public Copiable, public Affichable
{
public:
	Image(std::string nomImage, std::string dossier, int nCanaux, int nBitsParCanal, int nCouleurs);
	Image(const Image& image);
	virtual ~Image() = default;
	Image& operator=(const Image&);

	std::string getFichier() const;
	std::string getNom() const;
	std::string getDossier() const;
	std::string getId() const;
	unsigned int getTaille() const;
	unsigned int getHauteur() const;
	unsigned int getLargeur() const;
	void setDossier(const std::string& dossier);
	void setNom(const std::string&);

	bool operator==(const std::string& nomImage) const;

	std::pair<int, int> getPositionImage(const Image* image) const;
	void save();
	void load();

protected:
	unsigned int getNCanaux() const;
	int getTaillePaletteCouleurs() const;
	virtual unsigned int getLargeurCodage() const;
	virtual int calculerPaletteCouleurs(int valeur);

	virtual const unsigned char* getDataPtr(int i, int j) const = 0;
	virtual void decoderNB(const unsigned char valeur) = 0;
	virtual void decoderRGB(const unsigned char data_ptr[]) = 0;
	virtual void decoderGris(const unsigned char data_ptr[]) = 0;
	void decoderImage(const Image& image);

	virtual void reset() = 0;
	virtual const unsigned char* getPixelData(unsigned int index) const = 0;
	virtual int getIndexImage(const Image*) const = 0;

private:
	/*Fonction du TP1 à garder intactes*/
	void mettreAJourFichier();
	void afficher(std::ostream& sortie) const override;

	/*Attributs*/
	//std::vector<Pixel> pixels_;
	unsigned int nCanaux_;
	unsigned int nBitsParCanal_;
	unsigned int nCouleurs_;
	unsigned int largeur_; // Largeur de l'image
	unsigned int hauteur_; // Hauteur de l'image
	std::string id_;
	std::string nomImage_;
	std::string dossierImage_;
	std::string fichier_;
};

#endif image_h
