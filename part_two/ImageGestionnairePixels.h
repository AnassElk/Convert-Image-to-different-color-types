#ifndef TP4_GESTIONNAIREPIXELS_H
#define TP4_GESTIONNAIREPIXELS_H

#include <vector>
#include <algorithm>
#include "Pixel.h"
#include "Image.h"

using namespace std;

/*TODO: Convertir la classe ImageGestionnairePixels en classe générique où le nombre de canaux est générique*/
template<unsigned int nCanaux>
class ImageGestionnairePixels: public Image {
public:
    ImageGestionnairePixels(const std::string& nomImage, const std::string& dossier, int nBitsParCanal, int nCouleurs);
    ImageGestionnairePixels& operator=(const ImageGestionnairePixels& gestionnaire);

    
    const Pixel<nCanaux>& getPixel(int index) const;
    unsigned int getNbPixels() const;

    Pixel<nCanaux>& operator[](int index);
    ImageGestionnairePixels& operator+=(const Pixel<nCanaux>& pixel);

    int getIndexImage(const Image* image) const override;
    void reset() override;
    const unsigned char* getPixelData(unsigned int index) const override;
    const unsigned char* getDataPtr(int i, int j) const override;

private:
   // unsigned int nCanaux_;
    int chercherPremiereRangePixels(int, const ImageGestionnairePixels& pixels) const;
    std::vector<Pixel<nCanaux>> pixels_;
};


template<unsigned int nCanaux>
ImageGestionnairePixels<nCanaux>::ImageGestionnairePixels(const std::string& nomImage, const std::string& dossier, int nBitsParCanal, int nCouleurs) :
    Image(nomImage, dossier, nCanaux, nBitsParCanal, nCouleurs) {}

template<unsigned int nCanaux>
ImageGestionnairePixels<nCanaux>& ImageGestionnairePixels<nCanaux>::operator=(const ImageGestionnairePixels<nCanaux>& gestionnaire) {
    if (this != &gestionnaire) {
        Image::operator=(gestionnaire);
        pixels_.clear();
        for (auto& pixel : gestionnaire.pixels_) {
            pixels_.push_back(pixel);
        }
    }
    return *this;
}

template<unsigned int nCanaux>
const Pixel<nCanaux>& ImageGestionnairePixels<nCanaux>::getPixel(int index) const {
    return pixels_[index];
}

// le static cast permet de convertir le Nbpixels en size_t en unsigned int (type de retour)
template<unsigned int nCanaux>
unsigned int ImageGestionnairePixels<nCanaux>::getNbPixels() const { return static_cast<unsigned int>(pixels_.size()); }

template<unsigned int nCanaux>
int ImageGestionnairePixels<nCanaux>::getIndexImage(const Image* image) const {
    int index = -1;
    const ImageGestionnairePixels* img = dynamic_cast<const ImageGestionnairePixels*>(image);
    index = chercherPremiereRangePixels(0, *img);
    while (index >= 0) {
        for (unsigned int i = 1; i < img->getHauteur(); i++) {
            bool egaux =  equal (img->pixels_.begin(), img->pixels_.end(),
                                 pixels_.begin() +  i*static_cast<_int64>(img->getHauteur()));
            if (!egaux) {
                break;
            }
        }
 
        if (index >= 0) return index;
        else {
            index = chercherPremiereRangePixels(index, *img);
        }
    }
    return index;
}

template<unsigned int nCanaux>
void ImageGestionnairePixels<nCanaux>::reset() {
    pixels_.clear();
}

template<unsigned int nCanaux>
int ImageGestionnairePixels<nCanaux>::chercherPremiereRangePixels(int indexDepart, const ImageGestionnairePixels& image) const {
    auto it = search(pixels_.begin() + indexDepart, pixels_.end(), 
                     image.pixels_.begin(), image.pixels_.begin() + image.getLargeur());

    int index;
    if (it != pixels_.end()) {
        index = (int)(it - pixels_.begin());
    }
    else index = -1;
    
    return index;
}

template<unsigned int nCanaux>
Pixel<nCanaux>& ImageGestionnairePixels<nCanaux>::operator[](int index) {
    return pixels_[index];
}

template<unsigned int nCanaux>
ImageGestionnairePixels<nCanaux>& ImageGestionnairePixels<nCanaux>::operator+=(const Pixel<nCanaux>& pixel) {
    pixels_.push_back(pixel);
    return *this;
}

template<unsigned int nCanaux>
const unsigned char* ImageGestionnairePixels<nCanaux>::getPixelData(unsigned int index) const {
    return pixels_[index].getData();
}

template<unsigned int nCanaux>
const unsigned char* ImageGestionnairePixels<nCanaux>::getDataPtr(int i, int j) const
{
    return pixels_[static_cast<uint64_t>(i) * getLargeur() + j].getData();
}

#endif