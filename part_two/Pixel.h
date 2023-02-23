#ifndef TP4_PIXEL_H
#define TP4_PIXEL_H

/*TODO: Convertir la classe Pixel en classe générique où le nombre de canaux est générique*/
#include <algorithm>

using namespace std;

template<unsigned int nCanaux>

class Pixel
{
public:
	Pixel();
	Pixel(const unsigned char data[]);
	Pixel(const Pixel& pixel);
	Pixel& operator=(const Pixel& pixel);

	void setData(const unsigned char data[]);
	const unsigned char* getData() const;
	unsigned int getNCanaux() const;
	unsigned char getMoyenne() const;
	bool estBlanc() const;

	unsigned char& operator[](int i);
	bool operator==(const Pixel& pixel) const;
	bool operator!=(const Pixel& pixel) const;
	
private:
	//nCanaux nCanaux_;
	unsigned char data_[nCanaux];
};

template<unsigned int nCanaux>
Pixel<nCanaux>::Pixel()
{
	for (unsigned int i = 0; i < nCanaux; i++) {
		data_[i] = 0;
	}
}

template<unsigned int nCanaux>
Pixel<nCanaux>::Pixel(const unsigned char data[]) :
	Pixel()
{
	setData(data);
}

template<unsigned int nCanaux>
Pixel<nCanaux>::Pixel(const Pixel<nCanaux>& pixel)
{
	*this = pixel;
}

template<unsigned int nCanaux>
Pixel<nCanaux>& Pixel<nCanaux>::operator=(const Pixel<nCanaux>& pixel)
{
	setData(pixel.data_);
	return *this;
}

template<unsigned int nCanaux>
void Pixel<nCanaux>::setData(const unsigned char data[])
{
	for (unsigned int i = 0; i < nCanaux; i++) {
		data_[i] = data[i];
	}
}

template<unsigned int nCanaux>
const unsigned char* Pixel<nCanaux>::getData() const
{
	return data_;
}

template<unsigned int nCanaux>
unsigned int  Pixel<nCanaux>::getNCanaux() const { return nCanaux; }

template<unsigned int nCanaux>
unsigned char Pixel<nCanaux>::getMoyenne() const
{
	int somme = 0;
	for (unsigned int i = 0; i < nCanaux; i++) {
		somme += data_[i];
	}
	somme /= nCanaux;
	return somme;
}

template<unsigned int nCanaux>
bool Pixel<nCanaux>::estBlanc() const { return getMoyenne() > 128; }

template<unsigned int nCanaux>
unsigned char& Pixel<nCanaux>::operator[](int i)
{
	if (i < 0) i = 0;
	if (i > nCanaux) i = nCanaux - 1;

	return data_[i];
}

template<unsigned int nCanaux>
bool Pixel<nCanaux>::operator==(const Pixel<nCanaux>& pixel) const {
	for (unsigned int i = 0; i < nCanaux; i++) {
		if (data_[i] != pixel.data_[i]) return false;
	}
	return true;
}

template<unsigned int nCanaux>
bool Pixel<nCanaux>::operator!=(const Pixel<nCanaux>& pixel) const {
	return !(*this == pixel);
}
#endif