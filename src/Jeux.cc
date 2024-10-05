#include "Jeux.hpp"
#include "Ui.hpp"
using namespace std;

/**
 * @brief Constructeur de la classe Jeux
*/
Jeux::Jeux(){
    echequier = new Echequier();
    joueurBlanc = Joueur(Blanc);
    joueurNoir = Joueur(Noir);
    deplacementCont = DeplacementCont();
}

/**
 * @brief Permet de savoir si la saisie des coordonnées est correcte d'un point de vue syntaxique
 * 
 * @param cmd : coordonnées saisies par l'utilisateur
 * @return true : si la saisie est correcte
*/
bool Jeux::saisie_correcte(string const & cmd) {
regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);
}

/**
 * @brief Permet de savoir si la saisie des coordonnées est correcte d'un point de vue syntaxique pour le petit roque
 * 
 * @param cmd : coordonnées saisies par l'utilisateur
 * @return true : si la saisie est correcte
*/
bool Jeux::saisie_correcte_petitroque(string const & cmd) {
regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

/**
 * @brief Permet de savoir si la saisie des coordonnées est correcte d'un point de vue syntaxique pour le grand roque
 * 
 * @param cmd : coordonnées saisies par l'utilisateur
 * @return true : si la saisie est correcte
*/
bool Jeux::saisie_correcte_grandroque(string const & cmd) {
regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

/**
 * @brief Permet de retirer toute les prise en passant des pions du joueur, cette fonction est utilisée au début de chaque tour pour retirer les possibles prise 
 * en passant du tour précédent
 * 
 * @param joueur : joueur dont on veut retirer les prise en passant
 * @return void
*/
void Jeux::retirerPriseenPassant(Joueur joueur){
    for(int  i = 0 ; i < 8; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(echequier->get_echequier(i,j)->get_piece()!=nullptr){
                if(echequier->get_echequier(i,j)->get_piece()->get_couleur()==joueur.get_couleur() && echequier->get_echequier(i,j)->get_piece()->get_type()==pion){
                    Pion * p = (Pion*)echequier->get_echequier(i,j)->get_piece();
                    p->set_prise_en_passant(false);
                }
            }
        }
    }
}

/**
 * @brief Permet de faire le grand roque. On commence par vérifier que le roi et la tour n'ont pas bougé, puis on vérifie que les cases entre le roi et la tour sont vides
 * et que le roi ne passe pas par une case en échec. Si toutes ces conditions sont vérifiées, on effectue le grand roque
 * 
 * @param joueur : joueur qui veut effectuer le grand roque
 * @return true : si le grand roque a été effectué
 * @return false : si le grand roque n'a pas été effectué
*/
bool Jeux::grandroque(Joueur joueur){
    int x = 0;
    if (joueur.get_couleur() == Noir)
        x = 7;
    if (echequier->get_echequier(x, 4)->get_piece() != nullptr && echequier->get_echequier(x, 0)->get_piece() != nullptr && echequier->get_echequier(x, 4)->get_piece()->get_type() == roi && echequier->get_echequier(x, 0)->get_piece()->get_type() == tour && echequier->get_echequier(x, 1)->get_piece() == nullptr && echequier->get_echequier(x, 2)->get_piece() == nullptr && echequier->get_echequier(x, 3)->get_piece() == nullptr)
    {
        Roi *p = (Roi *)echequier->get_echequier(x, 4)->get_piece();
        Tour *t = (Tour *)echequier->get_echequier(x, 0)->get_piece();
        if (p->get_deplacer() == false && t->get_deplacer() == false)
        {
            Echequier *echequierTemp = new Echequier();
            echequierTemp->copy_echequier(echequier);
            echequierTemp->affiche();
            echequierTemp->deplacer(x, 4, x, 2);
            echequierTemp->deplacer(x, 0, x, 3);
            if (!en_Echec(joueur, echequierTemp))
            {
                echequier->deplacer(x, 4, x, 2);
                echequier->deplacer(x, 0, x, 3);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Permet de faire le petit roque. On commence par vérifier que le roi et la tour n'ont pas bougé, puis on vérifie que les cases entre le roi et la tour sont vides
 * et que le roi ne passe pas par une case en échec. Si toutes ces conditions sont vérifiées, on effectue le petit roque
 * 
 * @param joueur : joueur qui veut effectuer le petit roque
 * @return true : si le petit roque a été effectué
 * @return false : si le petit roque n'a pas été effectué
*/
bool Jeux::petitroque(Joueur joueur){
    int x = 0;
    if (joueur.get_couleur() == Noir)
        x = 7;
    if (echequier->get_echequier(x, 4)->get_piece() != nullptr && echequier->get_echequier(x, 7)->get_piece() != nullptr && echequier->get_echequier(x, 4)->get_piece()->get_type() == roi && echequier->get_echequier(x, 7)->get_piece()->get_type() == tour && echequier->get_echequier(x, 5)->get_piece() == nullptr && echequier->get_echequier(x, 6)->get_piece() == nullptr)
    {
        Roi *p = (Roi *)echequier->get_echequier(x, 4)->get_piece();
        Tour *t = (Tour *)echequier->get_echequier(x, 7)->get_piece();
        if (p->get_deplacer() == false && t->get_deplacer() == false)
        {
            Echequier *echequierTemp = new Echequier();
            echequierTemp->copy_echequier(echequier);
            echequierTemp->deplacer(x, 4, x, 6);
            echequierTemp->deplacer(x, 4, x, 6);
            if (!en_Echec(joueur, echequierTemp))
            {
                echequier->deplacer(x, 4, x, 6);
                echequier->deplacer(x, 7, x, 5);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Permet de traiter l'entrée utilisateur et de faire les actions correspondantes. 
 * On commence par afficher la couleur du joueur qui doit jouer. On vérifie ensuite si le joueur est en échec, si c'est le cas, on vérifie si le joueur est en échec et mat.
 * Si le joueur est en échec et mat, on affiche un message et on retourne -4. Si le joueur est en échec, on affiche un message. On vérifie ensuite si le joueur est en pat, si c'est le cas, on retourne -1.
 * On demande ensuite au joueur de rentrer les coordonnées de la pièce qu'il veut déplacer. Si le joueur veut abandonner, on retourne -2, si le joueur veut on retourne -1 et si le joueur veut quitter, on retourne -3.
 * On regarde si le joueur veut faire un roque et sinon on coninue. On vérifie ensuite que le déplacement de la pièce peut se faire et ne mettrait pas le roi en echec.
 * Si le déplacement est possible, on effectue le déplacement et on retourne true. Si le déplacement n'est pas possible, on retourne false.
 * Si le pion est au bout de la ligne, on demande au joueur quelle pièce il veut et on la place à la place du pion. On retourne ensuite true.
 * 
 * @param joueur : joueur qui doit jouer
 * @return int : état de la partie
 * @return -1 : si le joueur est en pat
 * @return -2 : si le joueur abandonne
 * @return -3 : si le joueur quitte
 * @return -4 : si le joueur est en échec et mat
 * @return 0 : si le déplacement n'est pas possible
 * @return 1 : si le déplacement est possible
*/
int Jeux::deplacer(Joueur joueur){
    Ui::affichetour(joueur.get_couleur());
    retirerPriseenPassant(joueur);
    bool isechec = en_Echec(joueur,echequier);
    if(isechec){
        if(echecEtMat(joueur,echequier)){
            Ui::affiche_echecetmat(joueur.get_couleur());
            return -4;
        }
        else
            Ui::affiche_echec(joueur.get_couleur());
    }
    if(pat(joueur,echequier))
        return -1;
    string deplacement = Ui::Coordonnees();

    if(deplacement == "/draw" || deplacement == "/resign" || deplacement == "/quit"){
        switch (deplacement[1])
        {
        case 'd':
            return -1;
            break;
        case 'r':
            return -2;
            break;
        case 'q':
            return -3;
            break;
        default:
            break;
        }
    }

    if(saisie_correcte_grandroque(deplacement)){
        return grandroque(joueur);
    }
    if(saisie_correcte_petitroque(deplacement)){
        return petitroque(joueur);
    }
    if(!saisie_correcte(deplacement)){
        return false;
    }
    int y1 = deplacement[0] - 'a';
    int x1 = deplacement[1] - '1';
    int y2 = deplacement[2] - 'a';
    int x2 = deplacement[3] - '1';
    if (deplacementCont.verifierDeplacement(x1, y1, x2, y2,joueur,this->echequier)==true){
        bool move = false;
        if(!isechec){
            Echequier* echequierTemp = new Echequier();
            echequierTemp->copy_echequier(echequier);
            echequierTemp->deplacer(x1, y1, x2, y2);
            if(!en_Echec(joueur,echequierTemp)){
                echequier->deplacer(x1, y1, x2, y2);
                move = true;
            }
            else{
                return false;
            }
        }
        else{
            Echequier* echequierTemp = new Echequier();
            echequierTemp->copy_echequier(echequier);
            echequierTemp->deplacer(x1, y1, x2, y2);
            if(!en_Echec(joueur,echequierTemp)){
                echequier->deplacer(x1, y1, x2, y2);
                move = true;
            }
            else{
                return false;
            }
        }
        if(move && echequier->get_echequier(x2,y2)->get_piece()->get_type()==pion && ((x2 ==0 && joueur.get_couleur()==Noir)||(x2==7 && joueur.get_couleur()==Blanc)) ){
                remplace_Pion(x2,y2,joueur,echequier);
        }
        return true;
    }
    return false;
}

/**
 * @brief Permet de vérifier si le joueur est en échec. On parcourt l'échiquier et on regarde oo est le roi du joueur. On parcourt ensuite l'échiquier et on regarde si une pièce adverse peut manger le roi.
 * Si c'est le cas, on retourne true, sinon on retourne false.
 * 
 * @param joueur : joueur dont on veut savoir s'il est en échec
 * @param echeq : échiquier
 * @return true : si le joueur est en échec
 * @return false : si le joueur n'est pas en échec
*/
bool Jeux::en_Echec(Joueur joueur, Echequier *echeq){
    int xRoi = 0;
    int yRoi = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(echeq->get_echequier(i, j)->get_piece() != nullptr && echeq->get_echequier(i, j)->get_piece()->get_type() == roi && echeq->get_echequier(i, j)->get_piece()->get_couleur() == joueur.get_couleur()){
                xRoi = i;
                yRoi = j;
            }
        }
    }
    for(int i = 0; i<8; i++){
        for(int j = 0 ; j<8 ; j++){
            if(echeq->get_echequier(i,j)->get_piece()!=NULL && echeq->get_echequier(i,j)->get_piece()->get_couleur()!=joueur.get_couleur()){
                if(joueur.get_couleur()==Blanc){
                    if(deplacementCont.verifierDeplacement(i,j,xRoi,yRoi,joueurNoir, echeq)){
                        return true;
                    }
                }
                else{
                    if(deplacementCont.verifierDeplacement(i,j,xRoi,yRoi,joueurBlanc, echeq)){
                        return true;
                    }
                }
            }
        }
    }       
    return false;
}

/**
 * @brief Permet de remplacer un pion par une autre pièce lorsque le pion arrive au bout de l'échiquier.
 * 
 * @param x1 : coordonnée x du pion
 * @param y1 : coordonnée y du pion
 * @param joueur : joueur qui joue
 * @param echequier : échiquier
 * @return true : si le pion a été remplacé
 * @return false : si le pion n'a pas été remplacé
*/
bool Jeux::remplace_Pion(int x1,int y1,Joueur joueur,Echequier* echequier){
    string tr = "";
    while (tr != "R" && tr != "B" && tr != "N" && tr != "Q"){
        tr = Ui::remplacePion();
    }
    switch (tr[0])
    {
    case 'R':
        {if(joueur.get_couleur() == Blanc){
            echequier->get_echequier(x1, y1)->set_piece(new Tour(joueur.get_couleur(),"\u2656"));
        }
        else{
            echequier->get_echequier(x1, y1)->set_piece(new Tour(joueur.get_couleur(),"\u265C"));
        }}
        break;
    case 'B':
        {if(joueur.get_couleur() == Blanc){
            echequier->get_echequier(x1, y1)->set_piece(new Fou(joueur.get_couleur(),"\u2657"));
        }
        else{
            echequier->get_echequier(x1, y1)->set_piece(new Fou(joueur.get_couleur(),"\u265D"));
        }}
        break;
    case 'N':
        {if(joueur.get_couleur() == Blanc){
            echequier->get_echequier(x1, y1)->set_piece(new Cavalier(joueur.get_couleur(),"\u2658"));
        }
        else{
            echequier->get_echequier(x1, y1)->set_piece(new Cavalier(joueur.get_couleur(),"\u265E"));
        }}
        break;
    case 'Q':
        {if(joueur.get_couleur() == Blanc){
            echequier->get_echequier(x1, y1)->set_piece(new Dame(joueur.get_couleur(),"\u2655"));
        }
        else{
            echequier->get_echequier(x1, y1)->set_piece(new Dame(joueur.get_couleur(),"\u265B"));
        }}
        break;
    default:
        return false;
        break;
    }
    return true;
    
}

/**
 * @brief Permet de vérifier si le joueur est en échec et mat. On parcourt l'échiquier et on regarde ou est le roi du joueur. On regarde si le roi peut se déplacer pour éviter l'echec.
 * Si c'est le cas, on retourne false, sinon on regarde si une pièce peut faire éviter l'échec. Si c'est le cas, on retourne false, sinon on retourne true.
 * 
 * @param joueur : joueur dont on veut savoir s'il est en échec et mat
 * @param echeq : échiquier
 * @return true : si le joueur est en échec et mat
 * @return false : si le joueur n'est pas en échec et mat
*/
bool Jeux::echecEtMat(Joueur joueur, Echequier *echeq){
    int xRoi = 0;
    int yRoi = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(echeq->get_echequier(i, j)->get_piece() != nullptr && echeq->get_echequier(i, j)->get_piece()->get_type() == roi && echeq->get_echequier(i, j)->get_piece()->get_couleur() == joueur.get_couleur()){
                xRoi = i;
                yRoi = j;
            }
        }
    }
    for(int i = -1; i<=1 ;i++){
        for(int j = -1; j<=1; j++ ){
            if( xRoi+i<8 && yRoi+j<8 && xRoi+i>=0 && xRoi+j>=0 && (echeq->get_echequier(xRoi+i,yRoi+j)->get_piece()==nullptr || echeq->get_echequier(xRoi+i,yRoi+j)->get_piece()->get_couleur()!=joueur.get_couleur())){
                Echequier* echequierTemp = new Echequier();
                echequierTemp->copy_echequier(echeq);
                echequierTemp->deplacer(xRoi,yRoi,xRoi+i,yRoi+j);
                if(!en_Echec(joueur, echequierTemp)){
                    Ui::deplacementroi(xRoi+i,yRoi+j);
                    return false;
                }
            }
        }
    }
    Ui::nondeplacementroi();
    for(int i = 0; i<8; i++){
        for(int j = 0 ; j<8 ; j++){
            if(echeq->get_echequier(i,j)->get_piece()!= nullptr && echeq->get_echequier(i,j)->get_piece()->get_couleur()==joueur.get_couleur()){
                for(int k = 0; k<8; k++){
                    for(int l = 0; l<8; l++){
                        Echequier* echequierTemp = new Echequier();
                        echequierTemp->copy_echequier(echeq);
                        if(deplacementCont.verifierDeplacement(i,j,k,l,joueur, echequierTemp)){
                            echequierTemp->deplacer(i,j,k,l);
                            if(!en_Echec(joueur, echequierTemp)){
                                Ui::deplacementpiece(i,j,k,l);
                                return false;
                            }
                        }
                        delete echequierTemp;
                    }
                }   
            }
        }
    }       
    return true;
}

/**
 * @brief on regarde si le joueur est en position de pat. On parcourt l'échiquier et on regarde si une pièce peut se déplacer. Si c'est le cas, on regarde si le roi est en échec après le déplacement.
 * Si c'est le cas, on continue, sinon on retourne false. Si on a parcouru tout l'échiquier, on retourne true.
 * 
 * @param joueur : joueur dont on veut savoir s'il est en pat
 * @param echeq : échiquier
 * @return true : si le joueur est en pat
 * @return false : si le joueur n'est pas en pat
*/
bool Jeux::pat(Joueur joueur, Echequier *echeq){
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(echeq->get_echequier(i,j)->get_piece()!= nullptr && echeq->get_echequier(i,j)->get_piece()->get_couleur()==joueur.get_couleur()){
                for(int k = 0; k<8; k++){
                    for(int l = 0; l<8; l++){
                        Echequier* echequierTemp = new Echequier();
                        echequierTemp->copy_echequier(echeq);
                        if(deplacementCont.verifierDeplacement(i,j,k,l,joueur, echequierTemp)){
                            echequierTemp->deplacer(i,j,k,l);
                            if(!en_Echec(joueur, echequierTemp)){
                                return false;
                            }
                        }
                        delete echequierTemp;
                    }
                }   
            }
        }
    }
    return true;
}

/**
 * @brief Permet de gérer les tours de la partie d'échec en faisant jouer les joueurs à tour de rôle. On affiche l'échiquier et on demande au joueur ce qu'il veut faire.
 * en fin de partie en affiche, grâce à la fonction Ui::affiche_finpartie, le joueur qui a gagné ainsi que le l'état de l'echequier sous forme canonique.
*/
void Jeux::jouer(){
    int k=0;
    while(true){
        echequier->affiche();
        if(k%2==0){
            int i = deplacer(joueurBlanc);
            if(i && !(i<0)){
                k++;
            }
            else if(i<0){
                Ui::affiche_finpartie(i,echequier,joueurBlanc.get_couleur());
                exit(0);
            }
        }
        else{
            int i = deplacer(joueurNoir);
            if(i && !(i<0)){
                k++;
            }
            else if(i<0){
                Ui::affiche_finpartie(i,echequier,joueurNoir.get_couleur());
                exit(0);
            }
        }
    }
}