/**
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"
#include <stdlib.h>
// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

bool compare(Piece pa, Piece pb)
{
  if ( (pa.x()==pb.x()) && (pa.y()==pb.y()) )
    return true;
  return false;
}

/**
 * Programme principal
 */
int main( int argc, char** argv )
{
  // instancie un objet p1 de type Piece
  Piece p1;
  // p1 est une piece blanche de coordonnees (3,3)
  p1.init( 3, 3, true );

  Piece p2(4,4,false);

  // On l'affiche
  p1.affiche();
  p2.affiche();

  Piece p3=p1;
  p1=p2;

  if (compare(p1,p2))
    cout << "memes positions" << endl;
  else
    cout << "differentes positions" << endl;

  //Piece tbl[4];

  //Joueur jb(true);
  //Joueur jn(false);
  JoueurBlanc jb;
  JoueurNoir jn;

  jb.affiche();
  jn.affiche();

  Echiquier e;
  jb.placerPieces(e);
  jn.placerPieces(e);
  int n;
  int i;
  n=1;
while (n>0) {

  system("CLS");
system("color 0F");
  e.affiche();
  i=jb.turn();
  if(i==0) n=i;
system("color F0");
  e.affiche();
  i=jb.turn();
  if(i==0) n=i;

}
  /*
  Roi rb(true);
  rb.affiche();
  Roi rn(false);
  rn.affiche();
  Reine qb(true);
  qb.affiche();
  Reine qn(false);
  qn.affiche();

  e.enleverPiece(5,1);
  e.placer(&rb);
  e.enleverPiece(5,8);
  e.placer(&rn);
  e.enleverPiece(4,1);
  e.placer(&qb);
  e.enleverPiece(4,8);
  e.placer(&qn);

  Piece* ptr;
  ptr=&rb;
  Roi* rptr;
  rptr=dynamic_cast<Roi*>(ptr);
  if (rptr==NULL)
    cout << "cast impossible" << endl;
  else
    cout << "cast reussi" << endl;
  */

  // les objets definis dans cette fonction sont automatiquement détruits.
  // Ex : p1
}
