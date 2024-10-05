#include <iostream>
#include <string>
#include <vector>
#include "Piece.hpp"
#pragma once
using namespace std;

class Square{
public:
    Square();
    ~Square();
    //void affiche();
    Piece* get_piece();
    void set_piece(Piece* p);
private:
    Piece* p;
};