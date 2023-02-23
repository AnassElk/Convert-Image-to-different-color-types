#include "ImageGris.h"
#include <string>

using namespace std;

ImageGris::ImageGris(string nomImage, string dossier): 
    ImageMonochromatique(nomImage, dossier, N_BITS_PAR_CANAL, NOMBRE_COULEURS) 
{
}

ImageGris::ImageGris(const Image& image): 
    ImageGris(image.getNom(), image.getDossier()) 
{
    decoderImage(image);
}

Image* ImageGris::copie() const 
{
    return new ImageGris(*this);
}