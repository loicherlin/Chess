#include <iostream>
#include <string>
#include <vector>
#include "Piece.hpp"
#pragma once
using namespace std;


class Roi : public Piece {
public:
    Roi();
    Roi(couleur_t couleur, std::string nom_affiche){
        this->couleur = couleur;
        this->nom_affiche = nom_affiche;
        this->capture = false;
        this->deplacer = false;
        if(couleur == Blanc){
            this->codeP.append("wK");
        }
        else{
            this->codeP.append("bK");
        }
    };
    void affiche(){
        cout << nom_affiche;
    }
    const type_piece_t get_type(){
        return roi;
    }
    // fonction qui permet de mettre deplacer a true
    void set_deplacer(){
        deplacer = true;
    }
    // fonction qui permet de savoir si le roi a deja bougé pour le roque
    bool get_deplacer(){
        return deplacer;
    }
    Piece* clone(){
        return new Roi(*this);
    }
private:
    // variable qui permet de savoir si le roi a deja bougé pour le roque
    bool deplacer = false;
};

