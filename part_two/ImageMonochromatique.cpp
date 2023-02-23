#include "ImageMonochromatique.h"
#include "Pixel.h"
#include <algorithm>

using namespace std;

ImageMonochromatique::ImageMonochromatique(const string& nomImage, const string& dossier, int nBitsParCanal, int nCouleurs) :
    ImageGestionnairePixels(nomImage, dossier, nBitsParCanal, nCouleurs)
{
}

unsigned char ImageMonochromatique::calculerValeurPixel(unsigned char valeur)
{
    return valeur;
}

void ImageMonochromatique::decoderNB(const unsigned char valeur)
{
    /*TODO: Initialiser la variable pixel*/
    Pixel<1> pixel;
    pixel[0] = valeur;
    *this += pixel;
}

void ImageMonochromatique::decoderRGB(const unsigned char data_ptr[])
{
    int somme = 0;
    for (unsigned int i = 0; i < 3; i++) {
        somme += data_ptr[i];
    }

    somme /= 3;
    return decoderNB(calculerValeurPixel(static_cast<unsigned char>(somme)));
}

void ImageMonochromatique::decoderGris(const unsigned char data_ptr[])
{
    return decoderNB(calculerValeurPixel(data_ptr[0]));
}

int ImageMonochromatique::getIndexImage(const Image* image) const {
    int index = -1;
    if (const ImageMonochromatique* imageMono = dynamic_cast<const ImageMonochromatique*>(image)) {
        index = ImageGestionnairePixels::getIndexImage(imageMono);
    }
    return index;
}