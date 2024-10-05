#include <regex>
#include "Echequier.hpp"
#include "Joueur.hpp"
#include "DeplacementCont.hpp"

#pragma once
using namespace std;


class Jeux {
public:
    Jeux();
    void jouer();
private:
    Echequier* echequier;
    Joueur joueurBlanc;
    Joueur joueurNoir;
    DeplacementCont deplacementCont;
    int deplacer(Joueur joueur);
    bool remplace_Pion(int x1,int y1,Joueur joueur,Echequier* echequier);
    bool echecEtMat(Joueur joueur, Echequier *echeq);
    bool pat(Joueur joueur, Echequier *echeq);
    bool en_Echec(Joueur joueur,Echequier* echequier);
    bool saisie_correcte(string const & cmd);
    bool saisie_correcte_petitroque(string const & cmd);
    bool saisie_correcte_grandroque(string const & cmd);
    void retirerPriseenPassant(Joueur joueur);
    bool grandroque(Joueur joueur);
    bool petitroque(Joueur joueur);

};
