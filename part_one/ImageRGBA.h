#ifndef TP3_IMAGERGBA_H
#define TP3_IMAGERGBA_H

#include "ImageRGB.h"
#include <memory>

using namespace std;


class ImageRGBA : public ImageRGB
{
public:
	ImageRGBA(std::string nomImage, std::string dossier);
	ImageRGBA(const ImageRGBA& image);
	ImageRGBA(const Image& image);
	ImageRGBA& operator=(const ImageRGBA& image);
	~ImageRGBA() = default;

	Image* copie() const override;
	const unsigned char* getDataPtr(int i, int j) const override;
	Pixel decoderNB(const unsigned char valeur) override;
	Pixel decoderRGB(const unsigned char data_ptr[]) override;
	Pixel decoderGris(const unsigned char data_ptr[]) override;

	void setAlpha(double alpha);

private:
	static const int N_BITS_PAR_CANAL = 32;
	static const int INDEX_ALPHA = 3;
	std::unique_ptr<unsigned char[]> data_ptr_;
};

#endif