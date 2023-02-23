#ifndef TP3_IMAGEMONOCHROMATIQUE_H
#define TP3_IMAGEMONOCHROMATIQUE_H

#include "Image.h"

using namespace std;


class ImageMonochromatique : public Image
{
public:
    ImageMonochromatique(const std::string& nomImage, const std::string& dossier, int nBitsParCanal, int nCouleurs);
    ~ImageMonochromatique() = default;

    virtual unsigned char calculerValeurPixel(unsigned char valeur);

    Pixel decoderNB(const unsigned char valeur) override;
    Pixel decoderRGB(const unsigned char data_ptr[]) override;
    Pixel decoderRGBA(const unsigned char data_ptr[]) override;
    Pixel decoderGris(const unsigned char data_ptr[]) override;

protected:
    static const int NOMBRE_CANAUX = 1;
};

#endif