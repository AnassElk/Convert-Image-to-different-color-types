#ifndef TP3_UTILITAIRECONVERSION_H
#define TP3_UTILITAIRECONVERSION_H

#include "ImageRGB.h"
#include "ImageRGBA.h"
#include "ImageGris.h"
#include "ImageNB.h"

namespace UtilitaireConversion {
    ImageRGB* toRGB(Image* image) 
    {
        ImageRGB* imageRGB = dynamic_cast<ImageRGB*>(image);
        if(imageRGB) return static_cast<ImageRGB*>(imageRGB->copie());
        else return new ImageRGB(*image);
    }// change

    ImageRGBA* toRGBA(Image* image) 
    {
        ImageRGBA* imageRGBA = dynamic_cast<ImageRGBA*>(image);
        if (imageRGBA) return static_cast<ImageRGBA*>(imageRGBA->copie());
        else return new ImageRGBA(*image);
    }

    ImageGris* toGris(Image* image) 
    {
        ImageGris* imageGris = dynamic_cast<ImageGris*>(image);
        if (imageGris) return static_cast<ImageGris*>(imageGris->copie());
        else return new ImageGris(*image);
    }

    ImageNB* toNB(Image* image) 
    {
        ImageNB* imageNB = dynamic_cast<ImageNB*>(image);
        if (imageNB) return static_cast<ImageNB*>(imageNB->copie());
        else return new ImageNB(*image);
    }
}

#endif