#include "Pixel.h"
#include "ImageRGB.h"
#include "ImageGris.h"
#include "ImageNB.h"
#include "Librairie.h"
#include "Image.h"
#include "Foncteurs.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "UtilitaireConversion.h"
#include <time.h>
#include <random>

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

    shared_ptr<Image> candidats[6] = {  make_shared<ImageNB>(justinOriginal, dossierOriginaux),
            make_shared<ImageRGB>(erinOriginal, dossierOriginaux),
            make_shared<ImageGris>(jagmeetOriginal, dossierOriginaux),
            make_shared<ImageNB>(justinOriginal + "_zoomin", dossierOriginaux),
            make_shared<ImageRGB>(erinOriginal + "_zoomin", dossierOriginaux),
            make_shared<ImageGris>(jagmeetOriginal + "_zoomin", dossierOriginaux)
    };

    for (auto& image : candidats) {
        image->load();
    }
    
    string nomsCandidats[3] = { justinOriginal, erinOriginal, jagmeetOriginal };
    string typeImage[3] = { "NB", "RGB", "GRIS" };
    int hauteurs[3] = { 267, 257, 276 };
    int largeurs[3] = { 189, 196, 183 };

    /*********************************TESTS FONCTEURS*********************************/

#if true
    // Test 1 - Tester la conversion 
    try {
        bool succes = true;
        // Test GenererCharsAleatoirement
        {
            srand(time(NULL));

            GenererCharsAleatoirement foncteur;
            const string charset = "0123456789AaBbCcDdEeFeGgHhIiJiKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz!@#$%^&*()_+=~";
            char charGenerer = foncteur();

            if (charset.find(charGenerer) == std::string::npos) {
                succes = false;
                std::cout << "Test GenererCharsAleatoirement failed" << std::endl;
            }
        }

        // Test ComparateurId
        {
            ComparateurId foncteur;
            bool estInferrieur = candidats[0]->getId() < candidats[1]->getId();
            if (estInferrieur != foncteur(candidats[0].get(), candidats[1].get())) {
                succes = false;
                std::cout << "Test ComparateurId failed" << std::endl;
            }
        }

        // Test ComparateurTaille
        {
            ComparateurTaille foncteur;
            bool estInferrieur = candidats[0]->getTaille() < candidats[1]->getTaille();
            if (estInferrieur != foncteur(candidats[0].get(), candidats[1].get())) {
                succes = false;
                std::cout << "Test ComparateurTaille failed" << std::endl;
            }
        }

        // Test ComparateurNom
        {
            ComparateurNom foncteur;
            bool estInferrieur = candidats[0]->getNom() < candidats[1]->getNom();
            if (estInferrieur != foncteur(candidats[0].get(), candidats[1].get())) {
                succes = false;
                std::cout << "Test ComparateurNom failed" << std::endl;
            }
        }
       
        // Test ImageEstDansIntervalleTailles
        { 
            int debut = 0;
            int fin = candidats[0]->getTaille();

            std::vector<const Image*> images;
            images.push_back(candidats[0].get());
            int cle = -1;
            const std::pair<int, std::vector<const Image*>> pairImage = make_pair(cle, images);

            ImageEstDansIntervalleTailles foncteur(debut, fin);

            succes &= foncteur(pairImage, candidats[0]->getTaille()) == true;
            succes &= foncteur(candidats[0]->getTaille(), pairImage) == false;
        }

        tests.push_back(succes);
    } catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif
    

    /***********************************TESTS Pixel***********************************/

#if true
    // Test 2 - Tester la classe generique Pixel 
    try {
        bool succes = true;
        {
            const unsigned int nCanaux = 4;
            const unsigned char data[4] = { 0, 1, 2, 3 };

            // constructeurs
            Pixel<nCanaux> pixel = Pixel<nCanaux>(data);
            Pixel<nCanaux> pixelCopie = Pixel<nCanaux>(pixel);
            Pixel<nCanaux> pixelAffecte;

            // operator=
            pixelAffecte = pixelCopie;

            succes &= pixel.getNCanaux() && 
                pixelCopie.getNCanaux() == nCanaux && 
                pixelAffecte.getNCanaux() == nCanaux;
        }
        tests.push_back(succes);
    }
    catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /***********************************TESTS Image***********************************/

#if true
    // Test 3 - Tester l'initialisation de id_
    try {
        bool succes = true;
        {
            ImageNB image = ImageNB("nomImage", "dossier");
            succes &= !(image.getId().empty());
        }
        tests.push_back(succes);
    }
    catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /**************TESTS ImageGestionnairePixels & ImageMonochromatique**************/

#if true
    // Test 4 - Tester la classe generique ImageGestionnairePixels &
    //          tester l'implementation de ImageMonochromatique
    try {
        bool succes = true;
        {
            // operator= 
            ImageNB image = *candidats[0].get();
            succes &= image.getNbPixels() == static_cast<ImageNB*>(candidats[0].get())->getNbPixels();

            // getters 
            int index;
            for (int i = 0; i < 3; i++) {
                index = rand() % image.getNbPixels();
                succes &= image.getPixel(index) == static_cast<ImageNB*>(candidats[0].get())->getPixel(index);
            }

            for (int i = 0; i < candidats[1]->getHauteur() * candidats[1]->getLargeur(); i++) {
                image += static_cast<ImageNB*>(candidats[1].get())->getPixel(i);
            }

            succes&= image.getIndexImage(candidats[0].get()) == 0;
        }
        tests.push_back(succes);
    }
    catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /************************************TESTS RGB************************************/

#if true
    // Test 5 - Tester l'implementation de RGB
    try {
        bool succes = true;
        {
            // operator=
            ImageRGB image = *candidats[0].get();
            int nbPixel = image.getNbPixels();
            const unsigned char data[4] = { 0, 1, 2, 3 };

            // decoderNB & decoderRGB
            image.decoderNB(0);
            image.decoderRGB(data);
            succes &= nbPixel + 2;
        }
        tests.push_back(succes);
    }
    catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /**********************************TESTS Librairie**********************************/

#if true
    // Test 6 - Tester l'implementation de Librairie
    try {
        bool succes = true;
        {
            Librairie librairie = Librairie("librairie");

            // ajouterImage 
            librairie.ajouterImage<ImageRGB>("image");
            succes &= librairie.getImagesParNom("image") != nullptr;

            // operateur= 
            Librairie librairieCopy = librairie;
            succes &= librairie.getNom() == librairieCopy.getNom() &&
                    librairie.getNombreImages() == librairieCopy.getNombreImages();

            // setNom 
            librairieCopy.setNom("librairieCopy");
            succes &= librairieCopy.getNom() == "librairieCopy";

            // opeator-= & operator[]
            string id = librairie.getImagesParNom("image")->getId();
            librairie -= id;
            succes &= librairie.getImagesParNom("image") == nullptr && librairie[id] == nullptr;

            string nom = candidats[0]->getNom();
            librairie.ajouterImage<ImageRGB>(nom);

            // getImagesParNom 
            succes &= librairie.getImagesParNom(nom)->getNom() == candidats[0]->getNom();

            // getImagesParNomPartiel 
            succes &= librairie.getImagesParNomPartiel(nom.substr(0, 3)).count(candidats[0].get());
        }
        tests.push_back(succes);
    }
    catch (...) {
        // if any test above fails
        tests.push_back(false);
    }
#else
    tests.push_back(false);
#endif

    /*********************************RESULTATS FINAUX*********************************/
    std::vector<float> ponderationTests = { 2, 1, 0.5, 2, 0.5, 2 };

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
