#include "ImageNB.h"

using namespace std;

ImageNB::ImageNB(const std::string& nomImage, const std::string& dossier) : ImageMonochromatique(nomImage, dossier, N_BITS_PAR_CANAL, NOMBRE_COULEURS) {
	data_ptr_ = std::make_unique<unsigned char>();
}

ImageNB::ImageNB(const ImageNB& image) : ImageNB(image.getNom(), image.getDossier()) {
	decoderImage(image);
}

ImageNB& ImageNB::operator=(const ImageNB& image) {
	Image::operator=(image);
	*data_ptr_ = *image.data_ptr_;
	return *this;
	// on a change
}

ImageNB::ImageNB(const Image& image) : ImageNB(image.getNom(), image.getDossier()) {
	decoderImage(image);
}


Image* ImageNB::copie() const {
	return new ImageNB(*this);
}

unsigned int ImageNB::getLargeurCodage() const {
	return static_cast<unsigned int>(ceil(getLargeur() / 8.0));
}

int ImageNB::calculerPaletteCouleurs(int valeur) {
	return valeur * 255;
}

unsigned char ImageNB::calculerValeurPixel(unsigned char valeur) {
	if (valeur > 128) return 255;
	else return 0;
}

const unsigned char* ImageNB::getDataPtr(int i, int j) const {
	// Nous effectuons une conversion de 2D en 1D de façon a parcourir le tableau
	// de pixels facilement
		unsigned int nBits = j * 8;
		*data_ptr_ = 0;
		for (int k = 7; k >= 0; k--) {
			if (nBits >= getLargeur()) { break; }
			int index = i * getLargeur() + j * 8 + 7 - k;
			if ((*const_cast<ImageNB*>(this))[static_cast<int>(index)].estBlanc()) {
				*data_ptr_ |= (1 << k);
			}
			nBits++;
		}
		return data_ptr_.get();

}