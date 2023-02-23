#ifndef TP4_IMAGERGB_H
#define TP4_IMAGERGB_H

#include <string>
#include "ImageGestionnairePixels.h"

/*TODO: Corriger l'instruction de dérivation*/
class ImageRGB : public ImageGestionnairePixels<3>
{
public:
	ImageRGB(const std::string& nomImage, const std::string& dossier, int nBitParCanal = 24);
	ImageRGB(const Image& image);
	virtual ~ImageRGB() = default;

	void decoderNB(const unsigned char valeur) override;
	void decoderRGB(const unsigned char data_ptr[]) override;
	void decoderGris(const unsigned char data_ptr[]) override;
	int getIndexImage(const Image* image) const override;
	Image* copie() const override;

protected:
	static const int NOMBRE_COULEURS = 0;
	static const int NOMBRE_CANAUX = 3;
};

#endif
