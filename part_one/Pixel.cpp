#include "Pixel.h"
#include <algorithm>

using namespace std;

Pixel::Pixel(const int nCanaux): 
	nCanaux_(nCanaux), 
	data_{ 0,0,0,0 } 
{
}

Pixel::Pixel(int nCanaux, const unsigned char data[]): 
	Pixel(nCanaux) 
{
	setData(data);
}

Pixel::Pixel(const Pixel& pixel) 
{
	*this = pixel;
}

Pixel& Pixel::operator=(const Pixel& pixel) 
{
	nCanaux_ = pixel.nCanaux_;
	setData(pixel.data_);
	return *this;
}

void Pixel::setData(const unsigned char data[]) 
{
	for (unsigned int i = 0; i < nCanaux_; i++) {
		data_[i] = data[i];
	}
}

const unsigned char* Pixel::getData() const 
{
	return data_;
}

int Pixel::getNCanaux() const { return nCanaux_; }

unsigned char Pixel::getMoyenne() const
{
	int somme = 0;
	for (unsigned int i = 0; i < nCanaux_; i++) {
		somme += data_[i];
	}
	somme /= nCanaux_;
	return somme;
}

bool Pixel::estBlanc() const { return getMoyenne() > 128; }

unsigned char& Pixel::operator[](int i) 
{
	if (i < 0) i = 0;
	if (i > 3) i = 3;

	return data_[i];
}