#ifndef TP3_PIXEL_H
#define TP3_PIXEL_H

#include <memory>
#include <iostream>

class Pixel
{
public:
	Pixel(const int nCanaux);
	Pixel(int nCanaux, const unsigned char data[]);
	Pixel(const Pixel& pixel);
	Pixel& operator=(const Pixel& pixel);

	void setData(const unsigned char data[]);
	const unsigned char* getData() const;
	int getNCanaux() const;
	unsigned char getMoyenne() const;
	bool estBlanc() const;

	unsigned char& operator[](int i);
	
private:
	unsigned int nCanaux_;
	unsigned char data_[4];
	static const unsigned char MIN_CONCENTRATION = 0;
	static const unsigned char MAX_CONCENTRATION = 255;
};

#endif