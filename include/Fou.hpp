#include <iostream>
#include <string>
#include <vector>
#include "Piece.hpp"
#pragma once
using namespace std;


class Fou : public Piece {
public:
    Fou();
    Fou(couleur_t couleur, std::string nom_affiche){
        this->couleur = couleur;
        this->nom_affiche = nom_affiche;
        this->capture = false;
        if(couleur == Blanc){
            this->codeP.append("wB");
        }
        else{
            this->codeP.append("bB");
        }
    };
    void affiche(){
        cout << nom_affiche;
    }
    const type_piece_t get_type(){
        return fou;
    }
    Piece* clone(){
        return new Fou(*this);
    }
private:
};

