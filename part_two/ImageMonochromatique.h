#ifndef TP4_IMAGEMONOCHROMATIQUE_H
#define TP4_IMAGEMONOCHROMATIQUE_H

#include "ImageGestionnairePixels.h"

/*TODO: Corriger l'instruction de dérivation*/
class ImageMonochromatique: public ImageGestionnairePixels<1>
{
public:
    ImageMonochromatique(const std::string& nomImage, const std::string& dossier, int nBitsParCanal, int nCouleurs);
    virtual ~ImageMonochromatique() = default;

    virtual unsigned char calculerValeurPixel(unsigned char valeur);

    void decoderNB(const unsigned char valeur) override;
    void decoderRGB(const unsigned char data_ptr[]) override;
    void decoderGris(const unsigned char data_ptr[]) override;

    int getIndexImage(const Image* image) const override;

protected:
    static const int NOMBRE_CANAUX = 1;
};

#endif
