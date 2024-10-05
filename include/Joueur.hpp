#include "Piece.hpp"
#pragma once

class Joueur
{
public:
    Joueur(){
        couleur = Blanc;
    }
    Joueur(couleur_t couleur){
        this->couleur = couleur;
    }
    couleur_t get_couleur(){
        return couleur;
    }
private:
    couleur_t couleur;
};

