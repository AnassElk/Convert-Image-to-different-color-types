#include "ImageMonochromatique.h"

using namespace std;

ImageMonochromatique::ImageMonochromatique(const std::string& nomImage, const std::string& dossier, int nBitsParCanal, int nCouleurs) : Image(nomImage, dossier, NOMBRE_CANAUX, nBitsParCanal, nCouleurs){

}


unsigned char ImageMonochromatique::calculerValeurPixel(unsigned char valeur) {
	return valeur;
}

Pixel ImageMonochromatique::decoderNB(const unsigned char valeur) {
	Pixel pixel(NOMBRE_CANAUX);
	pixel[0] = valeur;
	return pixel;
}
Pixel ImageMonochromatique::decoderRGB(const unsigned char data_ptr[]) {
	Pixel pixel(NOMBRE_CANAUX, data_ptr);
	return decoderNB(pixel.getMoyenne());
	// a revoir la moyenne ??????????????
}
Pixel ImageMonochromatique::decoderRGBA(const unsigned char data_ptr[]) {
	return decoderRGB(data_ptr);
}
Pixel ImageMonochromatique::decoderGris(const unsigned char data_ptr[]) {
	return decoderNB(*data_ptr);
}
