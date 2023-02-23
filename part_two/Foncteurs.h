#ifndef TP4_FONCTEURS_H
#define TP4_FONCTEURS_H

#include <ctime>
#include <random>
#include <utility>
#include "Image.h"

using namespace std;

//TODO: Créer les foncteurs demandés
class GenererCharsAleatoirement {
public:
    // todo
    //GenererCharsAleatoirement();
    char operator()() {
        return charset[rand() % 77];
    }
    
private:
    const char charset[77] = "0123456789AaBbCcDdEeFeGgHhIiJiKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz!@#$%^&*()_+=~";
};

class ComparateurId {
// todo
// Constructor and private part not SURE
public : 
    bool operator()(const Image* image1, const Image* image2) {
        return (image1->getId() < image2->getId());
    }
//private : 

};

class ComparateurTaille {
// todo
public :
    bool operator()(const Image* image1, const Image* image2) {
        return (image1->getTaille() < image2->getTaille());
    }
};

class ComparateurNom {
//  todo
public : 

    bool operator()(const Image* image1, const Image* image2) const {
        return (image1->getNom() < image2->getNom());
    }
};

class ImageEstDansIntervalleTailles {
public:
    ImageEstDansIntervalleTailles(int debut, int fin) : debut_(debut), fin_(fin) {}
    // todo
    bool operator() (pair<int, std::vector<const Image*>> paire, int) {
        return paire.first < debut_;
    }
    bool operator() (int , pair<int, std::vector<const Image*>> paire) {
        return paire.first > fin_;
    }
private:
    int debut_;
    int fin_;
};


#endif
