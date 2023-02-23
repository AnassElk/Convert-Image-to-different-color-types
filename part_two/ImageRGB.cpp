#include "ImageRGB.h"
#include "Pixel.h"

using namespace std;

ImageRGB::ImageRGB(const std::string& nomImage, const std::string& dossier, int nBitParCanal): 
	ImageGestionnairePixels(nomImage, dossier, 24, NOMBRE_COULEURS)
{
}

ImageRGB::ImageRGB(const Image& image) : ImageRGB(image.getNom(), image.getDossier(), 24) 
{
	decoderImage(image);
}

void ImageRGB::decoderNB(const unsigned char valeur) 
{
	/*TODO: Initialiser la variable pixel*/
	Pixel<3> pixel;
	for (unsigned int i = 0; i < NOMBRE_CANAUX; i++) {
		pixel[i] = valeur;
	}

	*this += pixel;
}

void ImageRGB::decoderRGB(const unsigned char data_ptr[]) 
{
	*this += Pixel<3>(data_ptr);/*TODO: Faire appel au constructeur par paramètres de Pixel*/
}

void ImageRGB::decoderGris(const unsigned char data_ptr[]) 
{
	decoderNB(data_ptr[0]);
}

Image* ImageRGB::copie() const 
{
	return new ImageRGB(*this);
}

int ImageRGB::getIndexImage(const Image* image) const {
	return ImageGestionnairePixels::getIndexImage(image);
}