#include "ImageRGB.h"

using namespace std;

ImageRGB::ImageRGB(const std::string& nomImage, const std::string& dossier, int nBitParCanal) : Image(nomImage, dossier, 3, 24, NOMBRE_COULEURS) {}
// peut etre changer getNCanaux par 3

ImageRGB::ImageRGB(const Image& image) : ImageRGB(image.getNom(), image.getDossier()){
	decoderImage(image);
	// constrcuteur change (24)
}

const unsigned char* ImageRGB::getDataPtr(int i, int j) const {
	return (*const_cast<ImageRGB*>(this))[static_cast<int>(i) * getLargeur() + static_cast<int>(j)].getData();
	// changer 
}

Pixel ImageRGB::decoderNB(const unsigned char valeur) {
	unsigned char data_ptr[4];
	data_ptr[3] = 0;
	data_ptr[2] = 0;
	data_ptr[1] = valeur;
	data_ptr[0] = valeur;

	Pixel pixel(3, data_ptr);
	// Pixel pixel(0);
	return pixel;
}

Pixel ImageRGB::decoderRGB(const unsigned char data_ptr[]){
	Pixel pixel(3, data_ptr); // getNCanaux
	return pixel;
}

Pixel ImageRGB::decoderRGBA(const unsigned char data_ptr[]) {
	return decoderRGB(data_ptr);
}

Pixel ImageRGB::decoderGris(const unsigned char data_ptr[]) {
	return decoderNB(data_ptr[0]);
	 
}

Image* ImageRGB::copie() const {
	return new ImageRGB(*this);
}