#include "Ui.hpp"
using namespace std;

/**
 * @brief affiche la couleur du tour courant
 * 
 * @param color : couleur du tour courant 
*/
void Ui::affichetour(couleur_t color)
{
    if(color == Blanc){
        cout << "Blanc : ";
    }
    else{
        cout << "Noir : ";
    }
}

/**
 * @brief affiche un message d'echec
 * 
 * @param color : couleur du tour courant
*/
void Ui::affiche_echec(couleur_t color){
    cout<<"vous êtes en echec : ";
}

/**
 * @brief affiche un message d'echec et mat et la couleur du gagnant
 * 
 * @param color : couleur du gagnant
*/
void Ui::affiche_echecetmat(couleur_t color){
    if(color == Blanc){
        cout<<"echec et mat, les noirs ont gagné"<<endl;
    }
    else{
        cout<<"echec et mat, les blancs ont gagné"<<endl;
    }
}

/**
 * @brief permet de choisir une piece a deplacer ainsi que sa destination
 * 
 * @return string : coordonnées de la piece a deplacer et de sa destination
*/
string Ui::Coordonnees(){
    string cmd;
    cin>>cmd;
    return cmd;
}


/**
 * @brief affiche le plateau canonique de l'echequier à la fin de la partie ainsi que le resultat de la partie
 * 
 * @param i : resultat de la partie
 * @param echequier : plateau canonique de l'echequier
 * @param color : couleur du gagnant
*/
void Ui::affiche_finpartie(int i, Echequier* echequier, couleur_t color){
    cout << "fin de partie" << endl;
    for(int i = 0; i<8; i++){
        for (int j = 0; j < 8; j++)
        {
            if ( echequier->get_echequier(i, j)->get_piece() != nullptr)
            {
                cout << echequier->get_echequier(i, j)->get_piece()->get_codeP();
            }
            cout << ",";
        }
    }
    switch (i)
    {
    case -1:
        cout << " 1/2-1/2";
        break;
    case -2:
        {if(color == Blanc){
            cout << " 0-1";
        }
        else{
            cout << " 1-0";
        }}
        break;
    case -3:
        cout << " ?-?";
        break;
    case -4:
        {if(color == Blanc){
            cout << " 0-1";
        }
        else{
            cout << " 1-0";
        }}
        break;
    default:
        cout << " ?-?";
        break;
    }
    cout << endl;
}

/**
 * @brief affiche et demande a l'utilisateur de choisir par quelle piece remplacer un pion
 * 
 * @return string : code de la piece choisie
*/
string Ui::remplacePion(){
    cout << "Quelle piece voulez vous ? (R, B, K, Q)" << endl;
    string cmd;
    cin>>cmd;
    return cmd;
}

/**
 * @brief affiche ou le roi peut se deplacer en cas d'echec
 * 
 * @param x : coordonnée x de la case ou le roi peut se deplacer
 * @param y : coordonnée y de la case ou le roi peut se deplacer
*/
void Ui::deplacementroi(int x, int y){
    cout << "Le roi peut se deplacer en " << x << " " << y << endl;
}
/**
 * @brief affiche le fait que le roi ne peut pas se deplacer
*/
void Ui::nondeplacementroi(){
    cout << "Le roi ne peut pas se deplacer" << endl;
}
/**
 * @brief affiche ou la piece peut se deplacer en cas d'echec pour l'éviter
 * 
 * @param i : coordonnée x de la piece
 * @param j : coordonnée y de la piece
 * @param x : coordonnée x de la case ou la piece peut se deplacer
 * @param y : coordonnée y de la case ou la piece peut se deplacer
*/
void Ui::deplacementpiece(int i, int j ,int x, int y){
    cout << "La piece en " << i << " " << j << " peut se deplacer en " << x << " " << y << endl;
}
