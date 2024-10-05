#include <iostream>
#include <string>
#include <vector>
#include "Piece.hpp"
#pragma once
using namespace std;


class Pion : public Piece {
public:
    Pion();
    Pion(couleur_t couleur, std::string nom_affiche){
        this->couleur = couleur;
        this->nom_affiche = nom_affiche;
        this->capture = false;
        this->prise_en_passant = false;
        if(couleur == Blanc){
            this->codeP.append("wP");
        }
        else{
            this->codeP.append("bP");
        }
    };
    void affiche(){
        cout << nom_affiche;
    }
    const type_piece_t get_type(){
        return pion;
    }
    // met la variable prise_en_passant à p
    void set_prise_en_passant(bool p){
        prise_en_passant = p;
    }
    // récupèRe la variable prise_en_passant
    bool get_prise_en_passant(){
        return prise_en_passant;
    }
    Piece* clone(){
        return new Pion(*this);
    }
private:
    //variable qui permet de savoir si le pion peut être pris en passant
    bool prise_en_passant = false;
};

