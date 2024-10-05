#include <iostream>
#include <string>
#include <vector>
#include "Piece.hpp"
#pragma once
using namespace std;


class Tour : public Piece {
public:
    Tour();
    Tour(couleur_t couleur, std::string nom_affiche){
        this->couleur = couleur;
        this->nom_affiche = nom_affiche;
        this->capture = false;
        if(couleur == Blanc){
            this->codeP.append("wR");
        }
        else{
            this->codeP.append("bR");
        }
    };
    void affiche(){
        cout << nom_affiche;
    }
    const type_piece_t get_type(){
        return tour;
    }
    // fonction qui permet de mettre deplacer a true
    void set_deplacer(){
        deplacer = true;
    }
    // fonction qui permet de savoir si la tour a deja bougé pour le roque
    bool get_deplacer(){
        return deplacer;
    }
    Piece* clone(){
        return new Tour(*this);
    }
private:
    // variable qui permet de savoir si la tour a deja bougé pour le roque
    bool deplacer = false;
};

