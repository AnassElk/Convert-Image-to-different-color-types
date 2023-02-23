#ifndef TP4_IMAGEGRIS_H
#define TP4_IMAGEGRIS_H

#include "ImageMonochromatique.h"
#include <string>

class ImageGris : public ImageMonochromatique
{
public:
    ImageGris(std::string nomImage, std::string dossier);
    ImageGris(const Image& image);
    virtual ~ImageGris() = default;

    Image* copie() const override;

private:
    static const int NOMBRE_COULEURS = 256;
    static const int N_BITS_PAR_CANAL = 8;
};

#endif