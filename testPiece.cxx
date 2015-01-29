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



bool isJoueurEnEchec(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
	cout<<"DEBUG:debut isJoueurEnEchec"<<endl;
	bool ret = false;
	vector<Piece*> findTheKing = joueurToCheck->getPieces();
	Piece* roi;
	for(vector<Piece*>::size_type i=0;i<findTheKing.size();i++){
		if(findTheKing[i]->codePiece()==(joueurToCheck->isWhite()?'R':'r')){
			roi = findTheKing[i];
		}
	}
	cout<<"DEBUG:roi trouvé"<<endl;
	for(vector<Piece*>::size_type i=0;i<attaquant->getPieces().size();i++){
		if(attaquant->getPieces()[i]->mouvementValide(e, roi->x(), roi->y())){
			ret = true;
		}
	}
	cout<<"DEBUG:fin isJoueurEchec"<<endl;
	return ret;
}

bool isJoueurMAT(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
	bool ret =false;
	int cpt=0;
	vector<Piece*> findTheKing = joueurToCheck->getPieces();
	Piece* roi;
	cout<<"DEBUG:debut isJoueurMat"<<endl;
	if(isJoueurEnEchec(joueurToCheck, attaquant,e))
	{
		cout<<"DEBUG:joueur en echec"<<endl;
		for(vector<Piece*>::size_type i=0;i<findTheKing.size();i++){
			if(findTheKing[i]->codePiece()==(joueurToCheck->isWhite()?'R':'r')){
				roi = findTheKing[i];
			}
		}
		vector<Piece*> pieces=attaquant->getPieces();
		for(vector<Piece*>::size_type i=0;i<pieces.size();i++){
			vector<int*> mouvements=pieces[i]->getMouvementsPossibles(e);
			vector<int*> posRoi=roi->getMouvementsPossibles(e);
			for(vector<int*>::size_type k=0; k<posRoi.size();k++){
				bool isEnEchec=false;
				for (vector<int*>::size_type j=0; j<mouvements.size();j++){
					if(posRoi[k][0]==mouvements[j][0] && posRoi[k][1]==mouvements[j][1]){
						isEnEchec=true;
					}
				}
				if(isEnEchec){cpt++;}
			}
		}
		cout<<cpt<<endl<<roi->getMouvementsPossibles(e).size()<<endl;
		ret=(cpt>=roi->getMouvementsPossibles(e).size());
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
	string text=isJoueurMAT(&jb, &jn,&e)?"MAT":"Pas MAT";
	cout<<text<<endl;
	e.deplacer(e.getPiece(2,1),4,6);
	e.affiche();
	text=isJoueurMAT(&jb, &jn,&e)?"MAT":"Pas MAT";
	cout<<text<<endl;
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

	// les objets definis dans cette fonction sont automatiquement dï¿½truits.
	// Ex : p1
}
