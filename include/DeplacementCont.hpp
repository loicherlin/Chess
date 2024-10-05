#include <iostream>
#include "Piece.hpp"
#include "Echequier.hpp"
#include "Joueur.hpp"
#pragma once

class DeplacementCont{
public:
    DeplacementCont(){};
    bool verifierDeplacement(int x1, int y1, int x2, int y2, Joueur joueur, Echequier* echequier);
    bool verifierDeplacement_Roi(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier);
    bool verifierDeplacement_Pion(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier);
    bool verifierDeplacement_Cavalier(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier);
    bool verifierDeplacement_Fou(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier);
    bool verifierDeplacement_Tour(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier);
private:
};