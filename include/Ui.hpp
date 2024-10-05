#include <iostream>
#include "Piece.hpp"
#include "Echequier.hpp"
#pragma once

class Ui{
public:
    Ui(){};
    static void affichetour(couleur_t color);
    static string Coordonnees();
    static string remplacePion();
    static void deplacementroi(int x, int y);
    static void nondeplacementroi();
    static void deplacementpiece(int i, int j ,int x, int y);
    static void affiche_echec(couleur_t color);
    static void affiche_echecetmat(couleur_t color);
    static void affiche_finpartie(int i, Echequier* echequier, couleur_t color);

private:
};

