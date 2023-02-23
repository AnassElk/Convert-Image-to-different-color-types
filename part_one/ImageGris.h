#ifndef TP3_IMAGEGRIS_H
#define TP3_IMAGEGRIS_H

#include "ImageMonochromatique.h"
#include <string>

using namespace std;

class ImageGris : public ImageMonochromatique
{
public:
    ImageGris(std::string nomImage, std::string dossier);
    ImageGris(const Image& image);
	~ImageGris() = default;

    Image* copie() const override;
    const unsigned char* getDataPtr(int i, int j) const override;

private:
    static const int NOMBRE_COULEURS = 256;
    static const int N_BITS_PAR_CANAL = 8;
};

#endif