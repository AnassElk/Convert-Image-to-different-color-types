#include "Pixel.h"
#include "ImageRGB.h"
#include "ImageRGBA.h"
#include "ImageGris.h"
#include "ImageNB.h"
#include "Librairie.h"
#include "Image.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "UtilitaireConversion.h"

using namespace std;

static unsigned char noir[3] = { 0, 0, 0 };
static unsigned char blanc[3] = { 255, 255, 255 };
static unsigned char vert[3] = { 0, 255, 0 };
static unsigned char bleu[3] = { 255, 0, 0 };
static unsigned char rouge[3] = { 0, 0, 255 };
static unsigned char jaune[3] = { 0, 255, 255 };
static unsigned char cyan[3] = { 255, 255, 0 };
static unsigned char magenta[3] = { 255, 0, 255 };
static const string dossierOriginaux = "./Originaux";
static const string dossierCopies = "./Copies";
static const string justinOriginal = "justin";
static const string erinOriginal = "erin";
static const string jagmeetOriginal = "jagmeet";

void save_image(Image& image, const string& nom) {
    image.setDossier(dossierCopies);
    image.setNom(nom);
    image.save();
}
// NOTE: Pour que le programme compile initialement, vous pouvez changer tous
// les #if true à des #if false, et mettre en commentaire tout le code qui a été
// écrit pour vous. Ainsi, vous pourrez graduellement les #if true et tester des
// petits blocs de code à la fois. Commencez par écrire vos constructeurs!

int main() {
    std::vector<bool> tests;
    stringstream buff;
    streambuf* coutbufMsg = std::cout.rdbuf();

    shared_ptr<Image> candidats[4] = {  make_shared<ImageNB>(justinOriginal, dossierOriginaux),
            make_shared<ImageRGBA>(erinOriginal, dossierOriginaux),
            make_shared<ImageRGB>(jagmeetOriginal, dossierOriginaux),
            make_shared<ImageGris>(justinOriginal, dossierOriginaux)
    };

    for (auto& image : candidats) {
        image->load();
    }
    
    string nomsCandidats[4] = { justinOriginal, erinOriginal, jagmeetOriginal, justinOriginal };
    string typeImage[4] = { "NB", "RGBA", "RGB", "GRIS" };
    int hauteurs[4] = { 267, 257, 276, 267 };
    int largeurs[4] = { 189, 196, 183, 189 };

    /*********************************TESTS UTILITAIRE_CONVERSION**********************/

#if true
    // Test 1 - Tester la conversion 
    try {
        bool succes = true;

        for (unsigned int i = 0; i < 3; i++) {
            Image* base = candidats[i].get();
            unique_ptr<Image> imageConvertedToNB = unique_ptr<Image>(UtilitaireConversion::toNB(base));
            save_image(*imageConvertedToNB, typeImage[i] + "_toNB");
            succes &= static_cast<ImageNB*>(imageConvertedToNB.get()) == imageConvertedToNB.get();
            unique_ptr<Image> imageConvertedToGRIS = unique_ptr<Image>(UtilitaireConversion::toGris(base));
            save_image(*imageConvertedToGRIS, typeImage[i] + "_toGris");
            succes &= static_cast<ImageGris*>(imageConvertedToGRIS.get()) == imageConvertedToGRIS.get();
            unique_ptr<Image> imageConvertedToRGB = unique_ptr<Image>(UtilitaireConversion::toRGB(base));
            save_image(*imageConvertedToRGB, typeImage[i] + "_toRGB");
            succes &= static_cast<ImageRGB*>(imageConvertedToRGB.get()) == imageConvertedToRGB.get();
            unique_ptr<Image> imageConvertedToRGBA = unique_ptr<Image>(UtilitaireConversion::toRGBA(base));
            save_image(*imageConvertedToRGBA, typeImage[i] + "_toRGBA");
            succes &= static_cast<ImageRGBA*>(imageConvertedToRGBA.get()) == imageConvertedToRGBA.get();
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
    
#else
    tests.push_back(false);
#endif

    /*********************************TESTS IMAGE**************************************/

#if true
    // Test 2 - Operateur <<
    try {
        bool succes = true;

        std::cout.rdbuf(buff.rdbuf());
        string sortieAttendue = "";
        for (unsigned int i = 0; i < 3; i++) {
            Image* image = candidats[i].get();
            sortieAttendue = "Fichier: " + image->getFichier() + "\n" + "Hauteur: " + to_string(image->getHauteur()) + "\n" + "Largeur: " + to_string(image->getLargeur()) + "\n";
            std::cout << *image;
            succes &= buff.str() == sortieAttendue;
            buff.str("");
        }
        buff.clear();
        std::cout.rdbuf(coutbufMsg);

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /*********************************TESTS IMAGE_RBG**********************************/

#if true
    // Test 3 - Constructeur par paramètres, decoderNB, decoderRGB, decoderRGBA, decoderGris et getDataPtr
    try {
        bool succes = true;

        for (unsigned int i = 0; i < 3; i++) {
            // Constructeur par paramètres, decoderNB, decoderRGB, decoder RGBA, decoderGris
            ImageRGB image(nomsCandidats[i], dossierOriginaux);
            image.load();
            succes &= image.getNom() == nomsCandidats[i];
            succes &= image.getDossier() == dossierOriginaux;
            succes &= image.getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= image.getHauteur() == hauteurs[i];
            succes &= image.getLargeur() == largeurs[i];

            // getDataPtr
            save_image(image, nomsCandidats[i] + "_RGB");
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

#if true
    // Test 4 - Constructeur par copie à partir de la classe de base, Copie
    try {
        bool succes = true;

        for (unsigned int i = 0; i < 4; i++) {
            // Constructeur par copie à partir de la classe de base, Copie
            Image* base = candidats[i].get();
            unique_ptr<ImageRGB> imageCopy = unique_ptr<ImageRGB>(UtilitaireConversion::toRGB(base));
            succes &= imageCopy->getNom() == nomsCandidats[i];
            succes &= imageCopy->getDossier() == dossierOriginaux;
            succes &= imageCopy->getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= imageCopy->getHauteur() == hauteurs[i];
            succes &= imageCopy->getLargeur() == largeurs[i];
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /*********************************TESTS IMAGE_RBGA*********************************/

#if true
    // Test 5 - Constructeur par paramètres, decoderNB, decoderRGB, decoderRGBA, decoderGris et getDataPtr
    try {
        bool succes = true;

        for (unsigned int i = 0; i < 3; i++) {
            // constructeur par paramètres, decoderNB, decoderRGB, decoderRGBA, decoderGris
            ImageRGBA image(nomsCandidats[i], dossierOriginaux);
            image.load();
            succes &= image.getNom() == nomsCandidats[i];
            succes &= image.getDossier() == dossierOriginaux;
            succes &= image.getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= image.getHauteur() == hauteurs[i];
            succes &= image.getLargeur() == largeurs[i];

            // getDataPtr
            save_image(image, nomsCandidats[i] + "_RGBA");
        }
        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

#if true
    // Test 6 - Constructeur par copie à partir de la classe de base, Copie et assignation
    try {
        bool succes = true;

        for (unsigned int i = 0; i < 4; i++) {
            // Constructeur par copie à partir de la classe de base et Copie
            Image* base = candidats[i].get();
            unique_ptr<ImageRGBA> image = unique_ptr<ImageRGBA>(UtilitaireConversion::toRGBA(base));
            succes &= image->getNom() == nomsCandidats[i];
            succes &= image->getDossier() == dossierOriginaux;
            succes &= image->getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= image->getHauteur() == hauteurs[i];
            succes &= image->getLargeur() == largeurs[i];

            // Copie par assignation et opérateur d'affectation
            ImageRGBA copy = *image;
            copy.setDossier(dossierCopies);
            succes &= image->getNom() == copy.getNom();
            succes &= image->getDossier() != copy.getDossier();
            succes &= image->getFichier() != copy.getFichier();
            succes &= image->getHauteur() == copy.getHauteur();
            succes &= image->getLargeur() == copy.getLargeur();
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

#if true
    // Test 7 - setAlpha
    try {
        bool succes = true;
        float alpha = 0.5;

        ImageRGBA image(nomsCandidats[0], dossierOriginaux);
        image.load();
        image.setAlpha(alpha);
        for (unsigned int i = 0; i < image.getLargeur() * image.getHauteur(); i++) {
            succes &= image[i][3] == static_cast<unsigned char>(alpha * 255);
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /*********************************TESTS IMAGE_MONOCHROMATIQUE**********************/
    /* Les tests monochromatiques sont compris dans les tests de ImageNB et ImageGris */
    /**********************************************************************************/

    /*********************************TESTS IMAGE_NB***********************************/

#if true
    // Test 8 - Constructeur par paramètres et getDataPtr
    try {
        bool succes = true;

        for (unsigned int i = 0; i < 3; i++) {
            // Constructeur par paramètres
            ImageNB image = ImageNB(nomsCandidats[i], dossierOriginaux);
            image.load();
            succes &= image.getNom() == nomsCandidats[i];
            succes &= image.getDossier() == dossierOriginaux;
            succes &= image.getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= image.getHauteur() == hauteurs[i];
            succes &= image.getLargeur() == largeurs[i];

            // getDataPtr
            save_image(image, nomsCandidats[i] + "_NB");
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

#if true
    // Test 9 - Constructeur par copie à partir de la classe de base, Copie et affectation
    try {
        bool succes = true;

        // Constructeur par copie à partir de la classe de base, Copie
        for (unsigned int i = 0; i < 3; i++) {
            Image *base = candidats[i].get();
            unique_ptr<ImageNB> image = unique_ptr<ImageNB>(UtilitaireConversion::toNB(base));
            succes &= image->getNom() == nomsCandidats[i];
            succes &= image->getDossier() == dossierOriginaux;
            succes &= image->getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= image->getHauteur() == hauteurs[i];
            succes &= image->getLargeur() == largeurs[i];

            // Copie par assignation et opérateur d'affectation
            ImageNB copy = *image;
            copy.setDossier(dossierCopies);
            succes &= image->getNom() == copy.getNom();
            succes &= image->getDossier() != copy.getDossier();
            succes &= image->getFichier() != copy.getFichier();
            succes &= image->getHauteur() == copy.getHauteur();
            succes &= image->getLargeur() == copy.getLargeur();
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

#if true
    // Test 10 - calculerValeurPixel
    try {
        bool succes = true;

        unique_ptr<ImageRGB> imageRGB = unique_ptr<ImageRGB>(UtilitaireConversion::toRGB(candidats[0].get()));
        unique_ptr<ImageGris> imageGRIS = unique_ptr<ImageGris>(UtilitaireConversion::toGris(candidats[0].get()));

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /*********************************TESTS IMAGE_GRIS*********************************/

#if true
    // Test 11 - Constructeur par paramètres et getDataPtr
    try {
        bool succes = true;

        for (unsigned int i = 0; i < 3; i++) {
            // Constructeur par paramètres
            ImageGris image = ImageGris(nomsCandidats[i], dossierOriginaux);
            image.load();
            succes &= image.getNom() == nomsCandidats[i];
            succes &= image.getDossier() == dossierOriginaux;
            succes &= image.getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= image.getHauteur() == hauteurs[i];
            succes &= image.getLargeur() == largeurs[i];

            // getDataPtr
            save_image(image, nomsCandidats[i] + "_GRIS");
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

#if true
    // Test 12 - Constructeur par copie à partir de la classe de base, Copie
    try {
        bool succes = true;

        // Constructeur par copie à partir de la classe de base, Copie
        for (unsigned int i = 0; i < 3; i++) {
            Image *base = candidats[i].get();
            unique_ptr<ImageGris> image = unique_ptr<ImageGris>(UtilitaireConversion::toGris(base));
            succes &= image->getNom() == nomsCandidats[i];
            succes &= image->getDossier() == dossierOriginaux;
            succes &= image->getFichier() == dossierOriginaux + "/" + nomsCandidats[i] + ".bmp";
            succes &= image->getHauteur() == hauteurs[i];
            succes &= image->getLargeur() == largeurs[i];
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /*********************************TESTS LIBRAIRIE**********************************/

#if true
    // Test 13 - Opérateurs +=, <<
    try {
        Librairie librairie(dossierOriginaux);
        bool succes = true;

        // Opérateur +=
        for (unsigned int i = 0; i < 3; i++) {
            // Constructeur par paramètres
            Image* image = candidats[i].get();
            librairie += image->getNom();
            succes &= librairie.getNombreImages() == i + 1;
            succes &= librairie[image->getNom()]->getNom() == image->getNom();
            succes &= librairie[image->getNom()]->getDossier() == image->getDossier();
            succes &= librairie[image->getNom()]->getFichier() == image->getFichier();
            succes &= librairie[image->getNom()]->getHauteur() == image->getHauteur();
            succes &= librairie[image->getNom()]->getLargeur() == image->getLargeur();
        }

        // Opérateur <<
        std::cout.rdbuf(buff.rdbuf());
        string sortieAttendue = "";
        for (unsigned int i = 0; i < 3; i++) {
            Image* image = candidats[i].get();
            sortieAttendue += "Fichier: " + image->getFichier() + "\n" + "Hauteur: " + to_string(image->getHauteur()) + "\n" + "Largeur: " + to_string(image->getLargeur()) + "\n\n";
        }
        sortieAttendue = "Nom librairie: " + librairie.getNom() + "\n" + sortieAttendue;
        cout << librairie;
        succes &= buff.str() == sortieAttendue;
        buff.str("");
        buff.clear();
        std::cout.rdbuf(coutbufMsg);

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /*********************************RESULTATS FINAUX*********************************/
    std::vector<float> ponderationTests = { 2, 0.25, 1, 0.25, 1, 0.25, 0.25,
            1, 0.25, 0.25, 1, 0.25, 0.25 };

    // Affichage
    float totalPoints = 0;
    for (std::size_t i = 0; i < tests.size(); i++) {
        std::string output = "Test " + std::to_string(i + 1) + ": ";
        if (tests[i] == true) {
            output += "OK!";
            std::stringstream stream;
            stream << ponderationTests[i] << '/' << ponderationTests[i];
            std::cout << std::left << std::setw(15) << std::left << output
                      << stream.str() << '\n';
            totalPoints += ponderationTests[i];
        }
        else {
            output += "ECHEC!";
            std::stringstream stream;
            stream << '0' << '/' << ponderationTests[i];
            std::cerr << std::left << std::setw(15) << output << "0/"
                      << ponderationTests[i] << '\n';
        }
    }
    std::stringstream stream;
    stream << totalPoints << "/"
           << std::accumulate(ponderationTests.begin(), ponderationTests.end(),
                   0.0f);
    std::cout << std::left << std::setw(16) << "TOTAL: " << stream.str() << '\n';
}
