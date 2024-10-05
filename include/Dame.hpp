#include <iostream>
#include <string>
#include <vector>
#include "Piece.hpp"
#pragma once
using namespace std;


class Dame : public Piece {
public:
    Dame();
    Dame(couleur_t couleur, std::string nom_affiche){
        this->couleur = couleur;
        this->nom_affiche = nom_affiche;
        this->capture = false;
        if(couleur == Blanc){
            this->codeP.append("wQ");
        }
        else{
            this->codeP.append("bQ");
        }
    };
    void affiche(){
        cout << nom_affiche;
    }
    const type_piece_t get_type(){
        return dame;
    }
    Piece* clone(){
        return new Dame(*this);
    }
private:
};

