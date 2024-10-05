#include "Square.hpp"
using namespace std;

Square::Square(){
}

Square::~Square(){
}

/**
 * @brief Permet de récupérer la pièce sur la case
 * 
 * @return Piece* : pointeur sur la pièce
*/
Piece* Square::get_piece(){
    return p;
}

/**
 * @brief Permet de modifier la pièce sur la case
 * 
 * @param p : pointeur sur la pièce
*/
void Square::set_piece(Piece* p){
    this->p = p;
}

