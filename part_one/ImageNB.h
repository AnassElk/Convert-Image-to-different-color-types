#ifndef TP3_IMAGENB_H
#define TP3_IMAGENB_H

#include <memory>
#include <string>
#include "Image.h"
#include "ImageMonochromatique.h"

using namespace std;

class ImageNB : public ImageMonochromatique
{
public:
    ImageNB(const std::string& nomImage, const std::string& dossier);
    ImageNB(const ImageNB& image);
    ImageNB& operator=(const ImageNB& image);
    ImageNB(const Image& image);
    ~ImageNB() = default;

    Image* copie() const;
    unsigned int getLargeurCodage() const override;
    int calculerPaletteCouleurs(int valeur) override;
    unsigned char calculerValeurPixel(unsigned char valeur) override;
    const unsigned char* getDataPtr(int i, int j) const override ;

private:
    static const int NOMBRE_COULEURS = 2;
    static const int N_BITS_PAR_CANAL = 1;
    std::unique_ptr<unsigned char> data_ptr_;
};

#endif

