#include <string>
#include <vector>
#include "Piece.hpp"
#pragma once
using namespace std;


class Cavalier : public Piece {
public:
    Cavalier();
    Cavalier(couleur_t couleur, std::string nom_affiche){
        this->couleur = couleur;
        this->nom_affiche = nom_affiche;
        this->capture = false;
        if(couleur == Blanc){
            this->codeP.append("wN");
        }
        else{
            this->codeP.append("bN");
        }
    };
    void affiche(){
        cout << nom_affiche ;
    }

    const type_piece_t get_type(){
        return cavalier;
    }

    Piece* clone(){
        return new Cavalier(*this);
    }
private:
};

