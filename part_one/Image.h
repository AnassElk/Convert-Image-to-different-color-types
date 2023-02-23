#ifndef TP3_IMAGE_H
#define TP3_IMAGE_H

#include "Pixel.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Affichable.h"
#include "Copiable.h"

using namespace std;

class Image : public Affichable, public Copiable
{
public:

	Image(std::string nomImage, std::string dossier, int nCanaux, int nBitsParCanal, int nCouleurs);
	Image(const Image& image);
	virtual ~Image() = default;
	Image& operator=(const Image&);

	std::string getFichier() const;
	std::string getNom() const;
	std::string getDossier() const;
	unsigned int getHauteur() const;
	unsigned int getLargeur() const;
	void setDossier(const std::string& dossier);
	void setNom(const std::string&);

	Pixel& operator[](int index);
	Image& operator+=(const Pixel& pixel);
	bool operator==(const std::string& nomImage) const;

	void save();
	void load();

protected:
	unsigned int getNCanaux() const;
	int getTaillePaletteCouleurs() const;
	virtual unsigned int getLargeurCodage() const;
	virtual int calculerPaletteCouleurs(int valeur);
	// changer les methodes virtual
	virtual const unsigned char* getDataPtr(int i, int j) const = 0 ;
	virtual Pixel decoderNB(const unsigned char valeur) = 0;
	virtual Pixel decoderRGB(const unsigned char data_ptr[]) = 0;
	virtual Pixel decoderRGBA(const unsigned char data_ptr[]) = 0;
	virtual Pixel decoderGris(const unsigned char data_ptr[]) = 0  ;
	void decoderImage(const Image& image);

private:
	/*Fonction du TP1 à garder intactes*/
	void mettreAJourFichier();
	void afficher(std::ostream& sortie) const override;

	/*Attributs*/
	std::vector<Pixel> pixels_;
	unsigned int nCanaux_;
	unsigned int nBitsParCanal_;
	unsigned int nCouleurs_;
	unsigned int largeur_; // Largeur de l'image
	unsigned int hauteur_; // Hauteur de l'image
	std::string nomImage_;
	std::string dossierImage_;
	std::string fichier_;
};

#endif image_h
