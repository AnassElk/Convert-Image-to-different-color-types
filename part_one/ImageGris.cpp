#include "ImageGris.h"

using namespace std;

ImageGris::ImageGris(std::string nomImage, std::string dossier) : ImageMonochromatique(nomImage, dossier, 8, 256){}

//ImageGris::ImageGris(const Image& image) :ImageMonochromatique(image.getNom(), image.getDossier(), 8, 256) {
//	decoderImage(image);

ImageGris::ImageGris(const Image& image) : ImageGris(image.getNom(), image.getDossier()) {
	decoderImage(image);
}


Image* ImageGris::copie() const {
	return new ImageGris(*this);
}

const unsigned char* ImageGris::getDataPtr(int i, int j) const {
	//decoderImage(dynamic_cast< const Image&>(*this));
	return &(*const_cast<ImageGris*>(this))[static_cast<int>(i) * getLargeur() + static_cast<int>(j)][0];//change

}
