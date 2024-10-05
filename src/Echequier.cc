#include "Echequier.hpp"
using namespace std;

/**
 * @brief Constructeur de la classe Echequier. Initialise un échiquier vide et place les pièces sur les cases de départ.
 * On ajoute les pièces dans les vecteurs piecesBlanc et piecesNoir pour pouvoir les supprimer à la fin de la partie et dans l'éventualité de compter
 * les points des joueurs.
*/
Echequier::Echequier () 
  {
    alloc_mem_echiquier();
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            echiquier[i][j]->set_piece(nullptr);
        }
    }
    //vector<Piece*> pieces;
    piecesBlanc.push_back(new Tour(Blanc,"\u2656"));
    this->echiquier[0][0]->set_piece(piecesBlanc[0]);
    piecesBlanc.push_back(new Cavalier(Blanc,"\u2658"));
    this->echiquier[0][1]->set_piece(piecesBlanc[1]);
    piecesBlanc.push_back(new Fou(Blanc,"\u2657"));
    this->echiquier[0][2]->set_piece(piecesBlanc[2]);
    piecesBlanc.push_back(new Dame(Blanc,"\u2655"));
    this->echiquier[0][3]->set_piece(piecesBlanc[3]);
    piecesBlanc.push_back(new Roi(Blanc,"\u2654"));
    this->echiquier[0][4]->set_piece(piecesBlanc[4]);
    piecesBlanc.push_back(new Fou(Blanc,"\u2657"));
    this->echiquier[0][5]->set_piece(piecesBlanc[5]);
    piecesBlanc.push_back(new Cavalier(Blanc,"\u2658"));
    this->echiquier[0][6]->set_piece(piecesBlanc[6]);
    piecesBlanc.push_back(new Tour(Blanc,"\u2656"));
    this->echiquier[0][7]->set_piece(piecesBlanc[7]);
    for(int i=0; i<8; i++){
        piecesBlanc.push_back(new Pion(Blanc,"\u2659"));
        this->echiquier[1][i]->set_piece(piecesBlanc[8+i]);
    }

    piecesNoir.push_back(new Tour(Noir,"\u265C"));
    this->echiquier[7][0]->set_piece(piecesNoir[0]);
    piecesNoir.push_back(new Cavalier(Noir,"\u265E"));
    this->echiquier[7][1]->set_piece(piecesNoir[1]);
    piecesNoir.push_back(new Fou(Noir,"\u265D"));
    this->echiquier[7][2]->set_piece(piecesNoir[2]);
    piecesNoir.push_back(new Dame(Noir,"\u265B"));
    this->echiquier[7][3]->set_piece(piecesNoir[3]);
    piecesNoir.push_back(new Roi(Noir,"\u265A"));
    this->echiquier[7][4]->set_piece(piecesNoir[4]);
    piecesNoir.push_back(new Fou(Noir,"\u265D"));
    this->echiquier[7][5]->set_piece(piecesNoir[5]);
    piecesNoir.push_back(new Cavalier(Noir,"\u265E"));
    this->echiquier[7][6]->set_piece(piecesNoir[6]);
    piecesNoir.push_back(new Tour(Noir,"\u265C"));
    this->echiquier[7][7]->set_piece(piecesNoir[7]);
    for(int i=0; i<8; i++){
        piecesNoir.push_back(new Pion(Noir,"\u265F"));
        this->echiquier[6][i]->set_piece(piecesNoir[8+i]);
    }
  }

/**
 * @brief Permet d'afficher l'échiquier dans le terminal
*/
  void Echequier::affiche()
  {
    string space5 = string(5, ' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    " << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i = 7; i >= 0; i--)
    {
        cout << i + 1 << " "; // numérotation ligne dans affichage
        for (int j = 0; j < 8; j++)
        {
            cout << "|";
            if (this->echiquier[i][j]->get_piece() != nullptr)
            {
              cout << "\u0020\u0020"; // U+0020 est un esapce utf-8 taille police
              this->echiquier[i][j]->get_piece()->affiche();
              cout << "\u0020"
                   << " ";
            }
            else
              cout << space5; // 2 ascii spaces
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}

/**
 * @brief Destruction de l'échiquier. On supprime les pièces de l'échiquier.
 * On libère la mémoire de l'échiquier.
*/
Echequier::~Echequier () 
  {
        for (int i=0;i<8;i++) {
                for (int j=0;j<8;j++) {
                        delete this->echiquier[i][j];
                }
        }
  }

/**
 * @brief Permet de déplacer une pièce de l'échiquier
 * @param x1 coordonnée x de la pièce à déplacer
 * @param y1 coordonnée y de la pièce à déplacer
 * @param x2 coordonnée x de la case où l'on veut déplacer la pièce
 * @param y2 coordonnée y de la case où l'on veut déplacer la pièce
*/
void Echequier::deplacer(int x1, int y1, int x2, int y2){
  this->echiquier[x2][y2]->set_piece(this->echiquier[x1][y1]->get_piece());
  this->echiquier[x1][y1]->set_piece(NULL);
}

/**
 * @brief Permet de récupérer une case de l'échiquier
 * @param x coordonnée x de la case à récupérer
 * @param y coordonnée y de la case à récupérer
 * @return la case de l'échiquier
*/
Square* Echequier::get_echequier(int x, int y){
  return this->echiquier[x][y];
}

/**
 * @brief Permet de copier un échiquier dans un autre ainsi que toutes les pièces de l'échiquier
 * @param echequier échiquier à copier
 * @return 0 si tout s'est bien passé
 * 
*/
int Echequier::copy_echequier(Echequier* echequier){
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if(echequier->echiquier[i][j]->get_piece() != nullptr){
        this->echiquier[i][j]->set_piece(echequier->echiquier[i][j]->get_piece()->clone());
      }
      else{
        this->echiquier[i][j]->set_piece(nullptr);
      }
    }
  }
  return 0;
}
