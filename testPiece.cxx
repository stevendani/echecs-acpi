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

bool deplacer(Piece* p, Joueur* opponent, Echiquier* e, int x, int y){
	if(p->mouvementValide(e,x,y)){
		if(e->getPiece(x,y)!=NULL){
			opponent->enleverPiece(e->getPiece(x,y));
		}
		e->deplacer(p,x,y);
		return true;
	}
	return false;
}

int* convertCoordonnees(string text){
	int* tab = new int[2];
	tab[0] = ::toupper(text[0]) -64;
	tab[1] = text[1] -48;
	return tab;
}

bool isCoordonneeValide(string text){
	if(text.size()==2){
		cout << "DEBUG : taille ok"<<endl;
		text[0] = ::toupper(text[0]);
		if(text[0]>='A' && text[0]<='H' && text[1]>='1' && text[1]<='8'){
			return true;
		}
	}
	return false;
}

bool isJoueurEnEchec(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
	cout<<"DEBUG:debut isJoueurEnEchec"<<endl;
	bool ret = false;
	vector<Piece*> findTheKing = joueurToCheck->getPieces();
	Piece* roi=NULL;
	for(vector<Piece*>::size_type i=0;i<findTheKing.size();i++){
		if(findTheKing[i]->codePiece()==(joueurToCheck->isWhite()?'R':'r')){
			roi = findTheKing[i];
			cout<<"DEBUG:roi trouvé"<<endl;
		}
	}
	if (roi==NULL){return false;}
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
	text=isJoueurMAT(&jn, &jb,&e)?"MAT":"Pas MAT";
	cout<<text<<endl;
	jn.enleverPiece(e.getPiece(5,8));
	e.deplacer(e.getPiece(5,1),5,8);
	e.affiche();
	text=isJoueurMAT(&jn, &jb,&e)?"MAT":"Pas MAT";
	cout<<text<<endl;
	text=isCoordonneeValide("A1")?"ok":"nope";
	cout<<text<<endl;
	text=isCoordonneeValide("11")?"ok":"nope";
	cout<<text<<endl;
	text=isCoordonneeValide("1A")?"ok":"nope";
	cout<<text<<endl;
	text=isCoordonneeValide("A1a")?"ok":"nope";
	cout<<text<<endl;
	text=isCoordonneeValide("a1")?"ok":"nope";
	cout<<text<<endl;
	text=isCoordonneeValide("i1")?"ok":"nope";
	cout<<text<<endl;
	text=isCoordonneeValide("a0")?"ok":"nope";
	cout<<text<<endl;
	text=isCoordonneeValide("a10")?"ok":"nope";
	cout<<text<<endl;
	int* coord = convertCoordonnees("b6");
	cout << coord[0] << endl << coord[1] << endl;


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
