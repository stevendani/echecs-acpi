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
	cout << "DEBUG : debut verif"<<endl;
	if(text.size()==2){
		cout << "DEBUG : taille ok"<<endl;
		text[0] = ::toupper(text[0]);
		if(text[0]>='A' && text[0]<='H' && text[1]>='1' && text[1]<='8'){
			cout << "DEBUG : dimension ok"<<endl;
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
			cout<<"DEBUG:roi trouvÃ©"<<endl<< roi->x() << endl << roi->y() << endl;
		}
	}
	if (roi==NULL){return false;}
	for(vector<Piece*>::size_type i=0;i<attaquant->getPieces().size();i++){
		if(attaquant->getPieces()[i]->mouvementValide(e, roi->x(), roi->y())){
			ret = true;
			vector<int*> mouvements=attaquant->getPieces()[i]->getMouvementsPossibles(e);
			cout<<"DEBUG:piece mettant en echec trouvÃ©"<<endl<< attaquant->getPieces()[i]->x() << endl << attaquant->getPieces()[i]->y() << endl;
			for (vector<int*>::size_type j=0; j<mouvements.size();j++){
				cout<< mouvements[j][0] <<endl<<mouvements[j][1]<<endl;
			}
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
bool
tour(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
	bool selection=false;
	int* coord;
	string coordonnee;
	e->affiche();
	while(!selection){
		cout << "entrée coordonnée piece" << endl;
		cin >> coordonnee;
		while(!isCoordonneeValide(coordonnee)){
			cout << "coordonee non valide" << endl;
			cout << "entrée coordonnée piece" << endl;
			cin >> coordonnee;
		}
		coord = convertCoordonnees(coordonnee);
		if (e->getPiece(coord[0],coord[1])!= NULL && (e->getPiece(coord[0],coord[1])->isWhite()==joueurToCheck->isWhite())){
			selection=true;
			cout << coord[0] << endl << coord[1] << endl;
		}else{
			cout << "pas de piece au coordonnee " << endl << coord[0] << endl << coord[1] << endl;
		}
	}
	e->affiche();
	bool mouvement=false;
	while(!mouvement){
		cout << "entrée nouvelle coordonnée piece" << endl;

		cin >> coordonnee;
		while(!isCoordonneeValide(coordonnee)){
			cout << "coordonee non valide" << endl;
			cout << "entrée coordonnée piece" << endl;
			cin >> coordonnee;
		}
		int* coord2 = convertCoordonnees(coordonnee);
		if (e->getPiece(coord[0],coord[1])->mouvementValide(e,coord2[0],coord2[1])){
			mouvement=true;
			deplacer(e->getPiece(coord[0],coord[1]),joueurToCheck, e, coord2[0],coord2[1]);
			cout << "deplacement effectuer " << endl;
			cout << coord2[1] << endl;
			if ((coord2[1]==(joueurToCheck->isWhite()?8:1))) {
				cout << "en bout de plateau " << endl;
				if (e->getPiece(coord2[0],coord2[1])->codePiece()==(joueurToCheck->isWhite()?'P':'p')){
					cout << "promotion demmarer " << endl;
					bool white=e->getPiece(coord2[0],coord2[1])->isWhite();
					joueurToCheck->enleverPiece(e->getPiece(coord2[0],coord2[1]));
					e->enleverPiece(coord2[0],coord2[1]);
					e->affiche();
					joueurToCheck->promotion(coord2[0],coord2[1],white,e);
					cout << "promotion effectuer " << endl;
				}
			}
		}else{
			cout << "deplacement impossible " << endl << coord2[0] << endl << coord2[1] << endl;
		}
	}
	return false;
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
	bool partie =true;
	while (partie){
		partie=true;
		cout <<"tour joueur blanc" << endl ;
		if (!isJoueurMAT(&jb, &jn,&e)){
			tour(&jb, &jn,&e);
		}else{
			partie=false;
		}
		cout <<"tour joueur noire" << endl ;
		if(partie){
			if (!isJoueurMAT(&jn, &jb,&e)){
				tour(&jn, &jb,&e);
			}else{
				partie=false;
			}
		}
	}


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
