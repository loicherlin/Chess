#include "DeplacementCont.hpp"
#include "Piece.hpp"

/**
 * @brief Verifie si le deplacement de la pièce qui se trouve en x1 y1 vers x2 y2 est possible, On commence par faire des testes simples.
 * Tout d'abord on verifie que les coordonnées sont bien dans l'échiquier, ensuite on verifie que la case de départ contient bien une pièce,
 * ensuite on verifie que la case d'arrivée ne contient pas une pièce de la même couleur que celle qui veut se déplacer, et enfin on verifie que
 * le déplacement est possible pour la pièce en question.
 * 
 * @param x1 : coordonnée x de la case de départ
 * @param y1 : coordonnée y de la case de départ
 * @param x2 : coordonnée x de la case d'arrivée
 * @param y2 : coordonnée y de la case d'arrivée
 * @param joueur : joueur qui joue
 * @param echequier : pointeur sur l'échiquier
*/
bool DeplacementCont::verifierDeplacement(int x1, int y1, int x2, int y2, Joueur joueur, Echequier* echequier){
    if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7){
        return false;
    }
    if(echequier->get_echequier(x1, y1)->get_piece() == nullptr){
        return false;
    }
    if(echequier->get_echequier(x2, y2)->get_piece() != nullptr){
        if(echequier->get_echequier(x1, y1)->get_piece()->get_couleur() == echequier->get_echequier(x2, y2)->get_piece()->get_couleur()){
            return false;
        }
    }
    if(echequier->get_echequier(x1, y1)->get_piece()->get_couleur() != joueur.get_couleur()){
        return false;
    }
    switch (echequier->get_echequier(x1, y1)->get_piece()->get_type()){

        case pion:
            return verifierDeplacement_Pion(x1, y1, x2, y2, joueur, echequier);
            break;

        case tour:
        {
            bool verif = verifierDeplacement_Tour(x1, y1, x2, y2, joueur, echequier);
            //si le deplacement est possible, on met le bool deplacer de la tour a true pour empecher le roque
            if(verif){
                Tour* p = (Tour*)echequier->get_echequier(x1, y1)->get_piece();
                p->set_deplacer();
            }
            return verif;}
            break;

        case fou:
            return verifierDeplacement_Fou(x1, y1, x2, y2, joueur, echequier);
            break;

        case dame:
            return verifierDeplacement_Fou(x1, y1, x2, y2, joueur,echequier) || verifierDeplacement_Tour(x1, y1, x2, y2, joueur,echequier);
            break;

        case roi:
        {
            bool verif = verifierDeplacement_Roi(x1, y1, x2, y2, joueur,echequier);
            //si le deplacement est possible, on met le bool deplacer du roi a true pour empecher le roque
            if(verif){
                Roi* p = (Roi*)echequier->get_echequier(x1, y1)->get_piece();
                p->set_deplacer();
            }
            return verif;}
            break;
        case cavalier:
            return verifierDeplacement_Cavalier(x1, y1, x2, y2, joueur,echequier);
            break;
        }
    return true;
}

/**
 * @brief Verifie si le deplacement de la pièce qui se trouve en x1 y1 vers x2 y2 est possible pour le roi.
 * On verifie que le déplacement est bien d'une case autour du roi.
 * 
 * @param x1 : coordonnée x de la case de départ
 * @param y1 : coordonnée y de la case de départ
 * @param x2 : coordonnée x de la case d'arrivée
 * @param y2 : coordonnée y de la case d'arrivée
 * @param joueur : joueur qui joue
 * @param echequier : pointeur sur l'échiquier
 * 
 * @return true si le deplacement est possible, false sinon
*/
bool DeplacementCont::verifierDeplacement_Roi(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier){
    if((x2 == x1+1 && y2 == y1) || (x2 == x1+1 && y2 == y1+1) || (x2 == x1 && y2 == y1+1) || (x2 == x1-1 && y2 == y1+1) || (x2 == x1-1 && y2 == y1) || (x2 == x1-1 && y2 == y1-1) || (x2 == x1 && y2 == y1-1) || (x2 == x1+1 && y2 == y1-1)){
        return true;
    }
    return false;
}

/**
 * @brief Verifie si le deplacement de la pièce qui se trouve en x1 y1 vers x2 y2 est possible pour un pion.
 * On verifie que le déplacement est bien en avant, que le pion ne va pas en arrière, que le pion ne va pas en diagonale sans manger une pièce,
 * que le pion ne va pas en avant de 2 cases si il n'est pas sur sa case de départ, et que le pion ne va pas en avant de 2 cases si il y a une pièce
 * sur la case devant lui.
 * On verifie aussi si la prise en passant est possible.
 * 
 * @param x1 : coordonnée x de la case de départ
 * @param y1 : coordonnée y de la case de départ
 * @param x2 : coordonnée x de la case d'arrivée
 * @param y2 : coordonnée y de la case d'arrivée
 * @param joueur : joueur qui joue
 * @param echequier : pointeur sur l'échiquier
 * 
 * @return true si le deplacement est possible, false sinon
*/
bool DeplacementCont::verifierDeplacement_Pion(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier){
    int couleur;
    if(joueur.get_couleur() == Blanc){
        couleur = 1;
    }
    else{
        couleur = -1;
    }
    if (y2 == y1 && x2 == x1 + 1 * couleur && echequier->get_echequier(x2, y2)->get_piece() == nullptr)
    {
        return true;
    }
    else if (y2 == y1 && x2 == x1 + 2 * couleur && ((x1 == 1 && joueur.get_couleur() == Blanc) || (x1 == 6 && joueur.get_couleur() == Noir)) && echequier->get_echequier(x2, y2)->get_piece() == nullptr && echequier->get_echequier(x1 + 1 * couleur, y1)->get_piece() == nullptr)
    {
        Pion *pion = (Pion *)echequier->get_echequier(x1, y1)->get_piece();
        pion->set_prise_en_passant(true);
        return true;
    }
    else if (((x2 == x1 + 1 * couleur && y2 == y1 + 1) || (x2 == x1 + 1 * couleur && y2 == y1 - 1)) && echequier->get_echequier(x2, y2)->get_piece() != nullptr && echequier->get_echequier(x2, y2)->get_piece()->get_couleur() != joueur.get_couleur())
    {
        return true;
    }
    else if (x2 == x1 + 1 * couleur && y2 == y1 + 1 && echequier->get_echequier(x2, y2)->get_piece() == nullptr && echequier->get_echequier(x1, y1 + 1)->get_piece() != nullptr && echequier->get_echequier(x1, y1 + 1)->get_piece()->get_type() == pion)
    {
        Pion *pion = (Pion *)echequier->get_echequier(x1, y1 + 1)->get_piece();
        if (pion->get_prise_en_passant() && pion->get_couleur() != joueur.get_couleur())
        {
            echequier->get_echequier(x1, y1 + 1)->set_piece(nullptr);
            return true;
        }
    }
    else if (x2 == x1 + 1 * couleur && y2 == y1 - 1 && echequier->get_echequier(x2, y2)->get_piece() == nullptr && echequier->get_echequier(x1, y1 - 1)->get_piece() != nullptr && echequier->get_echequier(x1, y1 - 1)->get_piece()->get_type() == pion)
    {
        Pion *pion = (Pion *)echequier->get_echequier(x1, y1 - 1)->get_piece();
        if (pion->get_prise_en_passant() && pion->get_couleur() != joueur.get_couleur())
        {
            echequier->get_echequier(x1, y1 - 1)->set_piece(nullptr);
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifie si le deplacement de la pièce qui se trouve en x1 y1 vers x2 y2 est possible pour un cavalier.
 * On verifie que le déplacement est bien en L.
 * 
 * @param x1 : coordonnée x de la case de départ
 * @param y1 : coordonnée y de la case de départ
 * @param x2 : coordonnée x de la case d'arrivée
 * @param y2 : coordonnée y de la case d'arrivée
 * @param joueur : joueur qui joue
 * @param echequier : pointeur sur l'échiquier
 * 
 * @return true si le deplacement est possible, false sinon
*/
bool DeplacementCont::verifierDeplacement_Cavalier(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier){
    if((x2 == x1+2 && y2 == y1+1) || (x2 == x1+2 && y2 == y1-1) || (x2 == x1-2 && y2 == y1+1) || (x2 == x1-2 && y2 == y1-1) || (x2 == x1+1 && y2 == y1+2) || (x2 == x1+1 && y2 == y1-2) || (x2 == x1-1 && y2 == y1+2) || (x2 == x1-1 && y2 == y1-2)){
            return true;
        }
    return false;
}

/**
 * @brief Verifie si le deplacement de la pièce qui se trouve en x1 y1 vers x2 y2 est possible pour une tour.
 * On verifie que le déplacement est bien en ligne droite.
 * On verifie que les cases entre la case de départ et la case d'arrivée sont vides.
 * 
 * @param x1 : coordonnée x de la case de départ
 * @param y1 : coordonnée y de la case de départ
 * @param x2 : coordonnée x de la case d'arrivée
 * @param y2 : coordonnée y de la case d'arrivée
 * @param joueur : joueur qui joue
 * @param echequier : pointeur sur l'échiquier
 * 
 * @return true si le deplacement est possible, false sinon
*/
bool DeplacementCont::verifierDeplacement_Fou(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier){
    int xf =0;
    int yf =0;
    if(x1>x2){
        xf = x1-x2;
    }
    else{
        xf = x2-x1;
    }
    if(y1>y2){
        yf = y1-y2;
    }
    else{
        yf = y2-y1;
    }
    if(xf!=yf){
        return false;
    }
    if(x2 > x1 && y2 > y1){
        for(int i=1; i<x2-x1; i++){
            if(echequier->get_echequier(x1+i, y1+i)->get_piece() != nullptr){
                return false;
            }
        }
        return true;
    }
    else if(x2 > x1 && y2 < y1){
        for(int i=1; i<x2-x1; i++){
            if(echequier->get_echequier(x1+i, y1-i)->get_piece() != nullptr){
                
                return false;
            }
        }
        return true;
    }
    else if(x2 < x1 && y2 < y1){
        for(int i=1; i<x1-x2; i++){
            if(echequier->get_echequier(x1-i, y1-i)->get_piece() != nullptr){
                
                return false;
            }
        }
        return true;
    }
    else if(x2 < x1 && y2 > y1){
        for(int i=1; i<x1-x2; i++){
            if(echequier->get_echequier(x1-i, y1+i)->get_piece() != nullptr){
                
                return false;
            }
        }
        return true;
    }
    return false;
}

/**
 * @brief Verifie si le deplacement de la pièce qui se trouve en x1 y1 vers x2 y2 est possible pour une tour.
 * On verifie que le déplacement est bien en ligne droite.
 * On verifie que les cases entre la case de départ et la case d'arrivée sont vides.
 * 
 * @param x1 : coordonnée x de la case de départ
 * @param y1 : coordonnée y de la case de départ
 * @param x2 : coordonnée x de la case d'arrivée
 * @param y2 : coordonnée y de la case d'arrivée
 * @param joueur : joueur qui joue
 * @param echequier : pointeur sur l'échiquier
 * 
 * @return true si le deplacement est possible, false sinon
*/
bool DeplacementCont::verifierDeplacement_Tour(int x1,int y1,int x2,int y2,Joueur joueur,Echequier* echequier){
    if (x2 == x1)
    {
        if (y2 > y1)
        {
            int y2temp = y2;
            y2 = y1;
            y1 = y2temp;
        }
        for (int i = y1 - 1; i > y2; i--)
        {
            if (echequier->get_echequier(x1, i)->get_piece() != nullptr)
            {

                return false;
            }
        }
        return true;
    }
    else if (y2 == y1)
    {
        if (x2 > x1){
            int x2temp = x2;
            x2 = x1;
            x1 = x2temp;
        }
        for (int i = x1 - 1; i > x2; i--)
        {
            if (echequier->get_echequier(i, y1)->get_piece() != nullptr)
            {

                return false;
            }
        }
        return true;
    }
    return false;
}
