#include <iostream>
#include <string>
#include <vector>
#include "Square.hpp"
#include "Piece.hpp"
#include "Pion.hpp"
#include "Tour.hpp"
#include "Fou.hpp"
#include "Cavalier.hpp"
#include "Dame.hpp"
#include "Roi.hpp"
#pragma once
using namespace std;

class Piece;
class Echequier {
public:
    Echequier();
    ~Echequier();
    void affiche();
    void deplacer(int x1, int y1, int x2, int y2);
    Square* get_echequier(int x, int y);
    int copy_echequier(Echequier* echequier);

private:
    Square *echiquier[8][8];
    vector<Piece*> piecesNoir;
    vector<Piece*> piecesBlanc;
    void alloc_mem_echiquier(){
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                echiquier[i][j] = new Square();
            }
        }
    }
};
