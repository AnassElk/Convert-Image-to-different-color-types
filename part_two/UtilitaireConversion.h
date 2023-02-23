#ifndef TP4_UTILITAIRECONVERSION_H
#define TP4_UTILITAIRECONVERSION_H

#include "ImageRGB.h"
#include "ImageGris.h"
#include "ImageNB.h"

namespace UtilitaireConversion {
    ImageRGB* toRGB(Image* image) 
    {
        if (dynamic_cast<ImageRGB*>(image)) return static_cast<ImageRGB*>(image->copie());
        return new ImageRGB(*image);
    }

    ImageGris* toGris(Image* image) 
    {
        if (dynamic_cast<ImageGris*>(image)) return static_cast<ImageGris*>(image->copie());
        return new ImageGris(*image);
    }

    ImageNB* toNB(Image* image) 
    {
        if (dynamic_cast<ImageNB*>(image)) return static_cast<ImageNB*>(image->copie());
        return new ImageNB(*image);
    }
}

#endif