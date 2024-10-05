#include <iostream>
#include <string>
#include <vector>
#pragma once
using namespace std;

typedef enum {Blanc=0, Noir=1} couleur_t;
typedef enum {roi=0, dame=1, tour=2, fou=3, cavalier=4, pion=5} type_piece_t;
class Piece{
public:
    //Constructeur par défaut
    Piece(){
        couleur = Blanc;
        nom_affiche = " ";
        capture = false;
    }
    //Constructeur de pièce
    Piece(couleur_t couleur, std::string nom_affiche){
        this->couleur = couleur;
        this->nom_affiche = nom_affiche;
        // si on rajoute les points on pourra utiliser cette variable pour savoir si la piece est sur le plateau ou non
        this->capture = false;
    };
    // méthode virtuel permet l'affichage de la pièce
    virtual void affiche() = 0;
    // méthode virtuel permet de retourne le type de la pièce
    virtual const type_piece_t get_type() = 0;
    // méthode virtuel permet de retourner un clone de la pièce
    virtual Piece* clone() = 0;
    //retourn la couleur de la pièce
    couleur_t get_couleur(){
        return couleur;
    }
    //retourn le nom de la pièce (pour l'affichage canonique)
    string get_codeP(){
        return codeP;
    }
protected:
    couleur_t couleur;
    std::string nom_affiche;
    bool capture;
    string codeP;
};