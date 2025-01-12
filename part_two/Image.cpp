#include "Image.h"
#include <iostream>
#include "bitmap.hpp"
#include <memory>
#include <algorithm>
#include "Foncteurs.h"

using namespace std;
using namespace bitmap;

Image::Image(std::string nomImage, std::string dossier, int nCanaux, int nBitsParCanal, int nCouleurs) :
	nomImage_(nomImage),
	dossierImage_(dossier),
	nCanaux_(nCanaux),
	nCouleurs_(nCouleurs),
	nBitsParCanal_(nBitsParCanal),
	fichier_(dossier + "/" + nomImage_ + ".bmp"),
	hauteur_(0),
	largeur_(0)
{
	//TODO: G�n�rer le id de l'image
	vector<char> stringId(20);
	generate(stringId.begin(), stringId.end(), GenererCharsAleatoirement());
	for (char caractere : stringId) {
		id_ += caractere;
	}
}

Image::Image(const Image& image)
{
	*this = image;
}

Image& Image::operator=(const Image& image)
{
	hauteur_ = image.hauteur_;
	largeur_ = image.largeur_;
	nomImage_ = image.nomImage_;
	dossierImage_ = image.dossierImage_;
	nCanaux_ = image.nCanaux_;
	nCouleurs_ = image.nCouleurs_;
	nBitsParCanal_ = image.nBitsParCanal_;
	mettreAJourFichier();

	return *this;
}

string Image::getFichier() const { return fichier_; }
string Image::getNom() const { return nomImage_; }
string Image::getDossier() const { return dossierImage_; }
string Image::getId() const { return id_; }
unsigned int Image::getTaille() const { return hauteur_ * largeur_; };
unsigned int Image::getHauteur() const { return hauteur_; }
unsigned int Image::getLargeur() const { return largeur_; }

void Image::setDossier(const std::string& dossier)
{
	dossierImage_ = dossier;
	mettreAJourFichier();
}

void Image::setNom(const std::string& nom)
{
	nomImage_ = nom;
	mettreAJourFichier();
}

bool Image::operator==(const std::string& nomImage) const
{
	return nomImage_ == nomImage;
}

std::pair<int, int> Image::getPositionImage(const Image* image) const {
	int index = -1;
	if (largeur_ >= image->largeur_ && hauteur_ >= image->hauteur_) {
		index = getIndexImage(image);
	}
	int j = -1;
	int i = -1;
	if (index >= 0) {
		j = index % largeur_;
		i = (index - j) / hauteur_;
	}
	return { i, j };
}

void Image::save() {
	std::ofstream stream(getFichier().c_str(), std::ios::binary);

	if (!stream)
	{
		std::cerr << "bitmap_image::save_image(): Error - Could not open file "
			<< fichier_ << " for writing!" << std::endl;
		return;
	}

	bitmap::bitmap_information_header bih;

	bih.width = largeur_;
	bih.height = hauteur_;
	bih.bit_count = nBitsParCanal_;
	bih.clr_important = 0;
	bih.clr_used = nCouleurs_;
	bih.compression = 0;
	bih.planes = 1;
	bih.size = bih.struct_size();
	bih.x_pels_per_meter = 0;
	bih.y_pels_per_meter = 0;
	bih.size_image = getHauteur() * getLargeurCodage();

	bitmap::bitmap_file_header bfh;

	bfh.type = 0x4d42;
	bfh.size = bfh.struct_size() + bih.struct_size() + getTaillePaletteCouleurs() + bih.size_image;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.off_bits = bih.struct_size() + bfh.struct_size() + getTaillePaletteCouleurs();

	bitmap::write_bfh(stream, bfh);
	bitmap::write_bih(stream, bih);

	if (getTaillePaletteCouleurs() > 0) {
		unique_ptr<RGBQUAD[]> quad = make_unique<RGBQUAD[]>(nCouleurs_);

		for (unsigned int i = 0; i < nCouleurs_; i++)
		{
			quad[i].b = quad[i].g = quad[i].r = calculerPaletteCouleurs(i);
			quad[i].reserved = 0;
		}
		stream.write(reinterpret_cast<const char*>(quad.get()), getTaillePaletteCouleurs());
	}
	unsigned int padding = (4 - ((getLargeurCodage()) % 4)) % 4;
	char padding_data[4] = { 0x00, 0x00, 0x00, 0x00 };

	for (unsigned int i = 0; i < hauteur_; i++)
	{
		for (unsigned int j = 0; j < min(getLargeurCodage(), static_cast<unsigned int>(largeur_)); j++) {
			const unsigned char* data_ptr = getDataPtr(i, j);
			stream.write(reinterpret_cast<const char*>(data_ptr), sizeof(unsigned char) * nCanaux_);
		}
		stream.write(padding_data, padding);
	}

	stream.close();
}

void Image::load()
{

	std::ifstream stream(fichier_.c_str(), std::ios::binary);

	if (!stream)
	{
		std::cerr << "bitmap_image::load_bitmap() ERROR: bitmap_image - "
			<< "file " << fichier_ << " not found!" << std::endl;
		return;
	}

	bitmap::bitmap_file_header bfh;
	bitmap::bitmap_information_header bih;

	bfh.clear();
	bih.clear();

	bitmap::read_bfh(stream, bfh);
	bitmap::read_bih(stream, bih);

	const int NUMBER_OF_COLORS = bih.clr_used;
	const int COLOR_PALETTE_SIZE = NUMBER_OF_COLORS * sizeof(RGBQUAD);

	RGBQUAD* quad = new RGBQUAD[NUMBER_OF_COLORS];
	if (bih.bit_count <= 8)
		stream.read(reinterpret_cast<char*>(quad), COLOR_PALETTE_SIZE);
	delete[] quad;

	largeur_ = bih.width;
	hauteur_ = bih.height;

	unsigned int bytes_per_pixel = max(bih.bit_count >> 3, 1);
	unsigned int encodingLargeur = largeur_;
	if (bih.bit_count == 1) encodingLargeur = static_cast<unsigned int>(ceil(bih.width / 8.0));

	unsigned int padding = (4 - ((bytes_per_pixel * encodingLargeur) % 4)) % 4;
	char padding_data[4] = { 0x00, 0x00, 0x00, 0x00 };

	reset();
	unsigned char data_ptr[4] = { 0,0,0,0 };
	for (unsigned int i = 0; i < getHauteur(); ++i)
	{
		unsigned int nBits = 1;
		for (unsigned int j = 0; j < encodingLargeur; j++) {
			stream.read(reinterpret_cast<char*>(data_ptr), sizeof(unsigned char) * bytes_per_pixel);
			if (bih.bit_count == 1) {
				for (int k = 7; k >= 0; k--) {
					if (nBits > getLargeur()) { break; }
					unsigned char valeur = (data_ptr[0] >> k) & 1 ? 0xFF : 0x00;
					decoderNB(valeur);
					nBits++;
				}
			}
			else if (bih.bit_count == 8) {
				decoderGris(data_ptr);
			}
			else if (bih.bit_count >= 24) {
				decoderRGB(data_ptr);
			}
		}

		stream.read(padding_data, padding);
	}
}

unsigned int Image::getNCanaux() const { return nCanaux_; }

int Image::getTaillePaletteCouleurs() const
{
	return nCouleurs_ * sizeof(RGBQUAD);
}

unsigned int Image::getLargeurCodage() const
{
	return nCanaux_ * largeur_;
}

int Image::calculerPaletteCouleurs(int valeur)
{
	return valeur;
}

void Image::decoderImage(const Image& image)
{
	hauteur_ = image.hauteur_;
	largeur_ = image.largeur_;
	for (unsigned int i = 0; i < getHauteur(); ++i)
	{
		for (unsigned int j = 0; j < getLargeur(); j++) {
			const unsigned char* data = image.getPixelData(static_cast<unsigned int>(static_cast<uint64_t>(i) * getLargeur() + j));
			if (image.nBitsParCanal_ <= 8) {
				decoderGris(data);
			}
			else {
				decoderRGB(data);
			}
		}
	}
}

void Image::mettreAJourFichier() { fichier_ = dossierImage_ + "/" + nomImage_ + ".bmp"; }

void Image::afficher(ostream& sortie) const
{
	sortie << "Fichier: " << fichier_ << endl;
	sortie << "Hauteur: " << hauteur_ << endl;
	sortie << "Largeur: " << largeur_ << endl;
}