/**
 * Header de Joueur.cxx
 *
 * @file Joueur.h
 */

#if !defined Joueur_h
#define Joueur_h

#include <vector>
#include "Piece.h"
#include "Echiquier.h"

using namespace std;

class Joueur
{
 protected:
  //Piece m_pieces[16];
  vector<Piece*> m_pieces;
 public:
  Joueur();
  Joueur(bool white);
  ~Joueur();
  void affiche();
  bool isWhite();
  vector<Piece*> getPieces();
  void placerPieces(Echiquier &e);
};

class JoueurBlanc : public Joueur
{
 public:
  JoueurBlanc();
  int turn();
};

class JoueurNoir : public Joueur
{
 public:
  JoueurNoir();
};

#endif
