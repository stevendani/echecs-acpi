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

bool isJoueurEnEchec(Joueur joueurToCheck,Joueur attaquant, Echiquier e){
	bool ret = false;
	vector<Piece*> findTheKing = joueurToCheck.getPieces();
	Piece* roi;
	for(vector<Piece*>::size_type i=0;i<findTheKing.size();i++){
		if(findTheKing[i]->codePiece()==(joueurToCheck.isWhite()?'R':'r')){
			roi = findTheKing[i];
		}
	}
	for(vector<Piece*>::size_type i=0;i<attaquant.getPieces().size();i++){
		if(attaquant.getPieces()[i]->mouvementValide(e, roi->x(), roi->y())){
			ret = true;
		}
	}
	return ret;
}

/**
 * Programme principal
 */
int main( int argc, char** argv )
{
  JoueurBlanc jb;
  JoueurNoir jn;

  jb.affiche();
  jn.affiche();

  Echiquier e;
  jb.placerPieces(e);
  jn.placerPieces(e);
  e.affiche();

  string text = e.getPiece(2,8)->mouvementValide(e,4,7)?"mouvement valide":"mouvement non valide";
  cout << text <<endl;
  e.deplacer(e.getPiece(1,2), 1,4);
  e.affiche();
  text = e.getPiece(1,4)->mouvementValide(e,1,6)?"mouvement valide":"mouvement non valide";
  cout << text <<endl;
/*while (n>0) {

  e.affiche();
  i=jb.turn();
  if(i==0) n=i;
  e.affiche();
  i=jb.turn();
  if(i==0) n=i;

}*/
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

  // les objets definis dans cette fonction sont automatiquement d�truits.
  // Ex : p1
}
