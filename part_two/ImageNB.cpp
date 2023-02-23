#include "ImageNB.h"
#include "bitmap.hpp"

using namespace std;
ImageNB::ImageNB(const std::string& nomImage, const std::string& dossier) :
    ImageMonochromatique(nomImage, dossier, N_BITS_PAR_CANAL, NOMBRE_COULEURS)
{
    data_ptr_ = make_unique<unsigned char>(0);
}

ImageNB::ImageNB(const ImageNB& image) :
    ImageMonochromatique(image), data_ptr_(make_unique<unsigned char>(0))
{
}

ImageNB::ImageNB(const Image& image) :
    ImageNB(image.getNom(), image.getDossier())
{
    decoderImage(image);
}

ImageNB& ImageNB::operator=(const ImageNB& image)
{
    if (this != &image) {
        ImageMonochromatique::operator=(image);
    }
    return *this;
}

Image* ImageNB::copie() const
{
    return new ImageNB(*this);
}

unsigned int ImageNB::getLargeurCodage() const
{
    return static_cast<unsigned int>(ceil(getLargeur() / 8.0));
}

int ImageNB::calculerPaletteCouleurs(int valeur)
{
    return valeur * 255;
}

unsigned char ImageNB::calculerValeurPixel(unsigned char valeur)
{
    return valeur > 128 ? 0xFF : 0x00;
}

const unsigned char* ImageNB::getDataPtr(int i, int j) const
{
    unsigned int nBits = j * 8;
    *data_ptr_ = 0;
    for (int k = 7; k >= 0; k--) {
        if (nBits >= getLargeur()) { break; }

        if (getPixel(static_cast<unsigned int>(static_cast<uint64_t>(i) * getLargeur() + static_cast<double>(j) * 8 + 7 - k)).estBlanc()) {
            *data_ptr_ |= (1 << k);
        }
        nBits++;
    }

    return data_ptr_.get();
}