#include "ImageRGBA.h"

using namespace std;

ImageRGBA::ImageRGBA(std::string nomImage, std::string dossier) : ImageRGB(nomImage, dossier){
	data_ptr_ = std::make_unique<unsigned char[]>(4);
}

 

ImageRGBA::ImageRGBA(const ImageRGBA& image) : ImageRGBA(image.getNom(), image.getDossier()) {
	decoderImage(image); // ajout 
}

// est ce qu en utilisant le constructeur de ImageRGB cela cmp n = 32
ImageRGBA::ImageRGBA(const Image& image)  : ImageRGBA(image.getNom(), image.getDossier()){
	decoderImage(image);
}


ImageRGBA& ImageRGBA::operator=(const ImageRGBA& image){
	Image::operator=(image);
	for (int i = 0; i <= INDEX_ALPHA; i++) {
		data_ptr_[i] = image.data_ptr_[i];
	}
	return *this;
}

Image* ImageRGBA::copie() const{
	return new ImageRGB(*this);
}

// a rechecker 
const unsigned char* ImageRGBA::getDataPtr(int i, int j) const
{
	int index1D = i * getLargeur() + j;
	const unsigned char* X = ((*const_cast<ImageRGBA*>(this))[index1D]).getData();
	for (int k = 0; k < 3; k++) {
		data_ptr_[k] = X[k] * X[INDEX_ALPHA] / 255;
	}
	data_ptr_[INDEX_ALPHA] = X[INDEX_ALPHA];
	return data_ptr_.get();
}

Pixel ImageRGBA::decoderNB(const unsigned char valeur) {
	unsigned char data_ptr[4];
	data_ptr[2] = valeur;
	data_ptr[1] = valeur;
	data_ptr[0] = valeur;
	data_ptr[INDEX_ALPHA] = 255;
	Pixel pixel(getNCanaux(), data_ptr);
	/*return ImageRGB::decoderNB(valeur);*/
	return pixel; // on peut utiliser decoderNB
}

Pixel ImageRGBA::decoderRGB(const unsigned char data_ptr[]) {
	unsigned char data[4];
	for (int i = 0; i < INDEX_ALPHA; i++) {
		data[i] = data_ptr[i];
	}
	data[INDEX_ALPHA] = 255;
	Pixel pixel(getNCanaux(), data);
	/*Pixel pixel = ImageRGB::decoderRGB(data_ptr);
	pixel[INDEX_ALPHA] = 255;*/
	return pixel;
}

Pixel ImageRGBA::decoderGris(const unsigned char data_ptr[]){
	unsigned char data[4];
	for (int i = 0; i < INDEX_ALPHA; i++) {
		data[i] = data_ptr[i];
	}
	data[INDEX_ALPHA] = 255;
	return ImageRGB::decoderGris(data);
}

void ImageRGBA::setAlpha(double alpha){
	for (int i = 0; i < getLargeur() * getHauteur(); i++) {
		(*this)[i][INDEX_ALPHA] = 255 * alpha;
	}
	/*data_ptr_[INDEX_ALPHA] = char(255 * alpha);*/
}
