#ifndef TP3_IMAGERGB_H
#define TP3_IMAGERGB_H

#include <string>
#include "Image.h"

using namespace std;

class ImageRGB : public Image
{
public:
	ImageRGB(const std::string& nomImage, const std::string& dossier, int nBitParCanal = 24);
	ImageRGB(const Image& image);
	~ImageRGB() = default;

	const unsigned char* getDataPtr(int i, int j) const override ;
	Pixel decoderNB(const unsigned char valeur) override;
	Pixel decoderRGB(const unsigned char data_ptr[]) override;
	Pixel decoderRGBA(const unsigned char data_ptr[]) override;
	Pixel decoderGris(const unsigned char data_ptr[]) override;
	Image* copie() const override;

protected:
	static const int NOMBRE_COULEURS = 0;
};

#endif