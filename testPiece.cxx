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
	vector<Piece*>* findTheKing = joueurToCheck->getPieces();
	Piece* roi=NULL;
	std::vector<Piece*>::iterator it = findTheKing->begin();
	while(it != findTheKing->end()){
		if((*it)->codePiece()==(joueurToCheck->isWhite()?'R':'r')){
			roi = (*it);
			cout<<"DEBUG:roi trouvé"<<endl<< roi->x() << endl << roi->y() << endl;
		}
		it++;
	}
	std::vector<Piece*>::iterator it2 = attaquant->getPieces()->begin();
	while(it2 != attaquant->getPieces()->end()){
		cout << (*it2)->codePiece() << endl;
		if((*it2)->mouvementValide(e, roi->x(), roi->y())){
			cout<<"DEBUG:joueur en echec"<<endl;
			ret = true;
		}
		it2++;
	}
	cout<<"DEBUG:fin isJoueurEchec"<<endl;
	return ret;
}
bool isPat(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
	bool ret = true;
	cout<<"DEBUG:debut isPAT"<<endl;
	if(!isJoueurEnEchec(joueurToCheck, attaquant,e))
	{
		int cpt=0;
		Piece* roi;
		std::vector<Piece*>::iterator it = joueurToCheck->getPieces()->begin();
		while(it != joueurToCheck->getPieces()->end()){
			if(!((*it)->codePiece()==(joueurToCheck->isWhite()?'R':'r'))){
				if((*it)->getMouvementsPossibles(e).size()>0){
					cout<<"DEBUG:mouvment possible autre rois"<<endl;
					ret=false;
				}
			}else{
				roi = (*it);
			}
			it++;
		}
		if(ret==true){
			vector<int*> posRoi=roi->getMouvementsPossibles(e);
			std::vector<int*>::iterator it2 = posRoi.begin();
			while(it2 != posRoi.end()){
				cout<<(*it2)[0]<<endl<<(*it2)[1]<<endl;
				bool isEnEchec=false;
				std::vector<Piece*>::iterator it3 =attaquant->getPieces()->begin();
				while(it3 != attaquant->getPieces()->end()){
					cout<<(*it2)[0]<<endl<<(*it2)[1]<<endl;
					if((*it3)->mouvementValide(e,(*it2)[0], (*it2)[1])){
						isEnEchec=true;
					}
					it3++;
				}
				if(isEnEchec){cpt++;}
				it2++;
			}
			ret=(cpt==posRoi.size());
		}
	}
	else{
		ret=false;
	}
	return ret;
}


bool isJoueurMAT(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
	bool ret =false;
	int cpt=0;
	vector<Piece*>* findTheKing = joueurToCheck->getPieces();
	Piece* roi;
	cout<<"DEBUG:debut isJoueurMat"<<endl;
	if(isJoueurEnEchec(joueurToCheck, attaquant,e))
	{
		std::vector<Piece*>::iterator it = findTheKing->begin();
		while(it != findTheKing->end()){
			if((*it)->codePiece()==(joueurToCheck->isWhite()?'R':'r')){
				roi = (*it);
			}
			it++;
		}
		vector<int*> posRoi=roi->getMouvementsPossibles(e);
		std::vector<int*>::iterator it2 = posRoi.begin();
		cout<<"DEBUG:debut isJoueurMat"<<endl;
		while(it2 != posRoi.end()){
			cout<<(*it2)[0]<<endl<<(*it2)[1]<<endl;
			bool isEnEchec=false;
			std::vector<Piece*>::iterator it3 = attaquant->getPieces()->begin();
			while(it3 != attaquant->getPieces()->end()){
				cout<<(*it2)[0]<<endl<<(*it2)[1]<<endl;
				if((*it3)->mouvementValide(e,(*it2)[0],(*it2)[1])){
					isEnEchec=true;
					std::vector<Piece*>::iterator it4 = findTheKing->begin();
					while(it4 != findTheKing->end()){
						if ((*it4)->mouvementValide(e,(*it3)->x(), (*it3)->y())){
							isEnEchec=false;
							cout<<"mangeable"<<endl;
						}
						it4++;
					}
				}
				it3++;
			}
			if(isEnEchec){cpt++;}
			it2++;
		}
		cout<<"DEBUG:debut isJoueurMat"<<endl;
		bool interupt = false;
		std::vector<Piece*>::iterator it5 = joueurToCheck->getPieces()->begin();
		while(it5 != joueurToCheck->getPieces()->end()){
			vector<int*> mouvements= (*it5)->getMouvementsPossibles(e);
			std::vector<int*>::iterator it6 = mouvements.begin();
			while(it6 != mouvements.end()){
				int origX = (*it5)->x();
				int origY = (*it5)->y();
				e->deplacer((*it5), (*it6)[0], (*it6)[1]);
				if(!isJoueurEnEchec(joueurToCheck, attaquant, e)){
					interupt = true;
					cout << "iterruption possible" << endl << origX << origY << endl << (*it6)[0] << (*it6)[1] << endl;
				}
				e->deplacer((*it5),origX, origY);
				it6++;
			}
			it5++;
		}
		cout<<"DEBUG:debut isJoueurMat"<<endl;
		cout<<cpt<<endl<<roi->getMouvementsPossibles(e).size()<<endl;
		ret=(cpt==posRoi.size() && !interupt);
	}
	return ret;
}
void
tour(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
	bool selection=false;
	int* coord;
	string coordonnee;
	e->affiche();
	while(!selection){
		cout << "entree coordonn�e piece" << endl;
		cin >> coordonnee;
		while(!isCoordonneeValide(coordonnee)){
			cout << "coordonee non valide" << endl;
			cout << "entree coordonnee piece" << endl;
			cin >> coordonnee;
		}
		int* coord1 = convertCoordonnees(coordonnee);
		if (e->getPiece(coord1[0],coord1[1])!= NULL && (e->getPiece(coord1[0],coord1[1])->isWhite()==joueurToCheck->isWhite())){

			if (e->getPiece(coord1[0],coord1[1])->getMouvementsPossibles(e).size()>0){
				selection=true;
				cout << coord1[0] << endl << coord1[1] << endl;
			}else{
				cout << " pas de mouvement disponible avec cette pi�ce" << endl;
			}
		}else{
			cout << "pas de piece au coordonnee " << endl << coord1[0] << endl << coord1[1] << endl;
		}
		delete[] coord1;
	}
	coord = convertCoordonnees(coordonnee);
	e->affiche();
	bool mouvement=false;
	while(!mouvement){
		cout << "entr�e nouvelle coordonn�e piece" << endl;
		cin >> coordonnee;
		while(!isCoordonneeValide(coordonnee)){
			cout << "coordonee non valide" << endl;
			cout << "entr�e coordonn�e piece" << endl;
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
		delete[] coord2;
	}
	delete[] coord;
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
		if(!isPat(&jb, &jn,&e)){
			if (!isJoueurMAT(&jb, &jn,&e)){
				cout <<" _ _ _    _   _   _ _ _   "<<endl;
				cout <<"|_   _| / _ \\| | | | _ \\  "<<endl;
				cout <<"  | |  | (_) | |_| |   /  "<<endl;
				cout <<"  |_|   \\___/ \\___/|_|_\\  "<<endl;
				cout <<"                       "<<endl;
				cout <<"//   _                               _     _                  "<<endl;
				cout <<"//  (_) ___  _   _  ___ _   _ _ __  | |__ | | __ _ _ __   ___ "<<endl;
				cout <<"//  | |/ _ \\| | | |/ _ | | | | '__| | '_ \\| |/ _` | '_ \\ / __|"<<endl;
				cout <<"//  | | (_) | |_| |  __| |_| | |    | |_) | | (_| | | | | (__ "<<endl;
				cout <<"// _/ |\\___/ \\__,_|\\___|\\__,_|_|    |_.__/|_|\\__,_|_| |_|\\___|"<<endl;
				cout <<"//|__/                                                        "<<endl;
				tour(&jb, &jn,&e);
			}else{
				partie=false;
				cout <<" _______  _______  _______  _______    _______           _______  _______ "<<endl;
				cout <<"(  ____ \(  ___  )(       )(  ____ \\  (  ___  )|\\     /|(  ____ \\(  ____ )"<<endl;
				cout <<"| (    \\/| (   ) || () () || (    \\/  | (   ) || )   ( || (    \\/| (    )|"<<endl;
				cout <<"| |      | (___) || || || || (__      | |   | || |   | || (__    | (____)|"<<endl;
				cout <<"| | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)"<<endl;
				cout <<"| | \\_  )| (   ) || |   | || (        | |   | | \\ \\_/ / | (      | (\\ (   "<<endl;
				cout <<"| (___) || )   ( || )   ( || (____/\\  | (___) |  \\   /  | (____/\\| ) \\ \\__"<<endl;
				cout <<"(_______)|/     \\||/     \\|(_______/  (_______)   \\_/   (_______/|/   \\__/"<<endl;
				cout <<"//     _                               _     _                  "<<endl;
				cout <<"//    (_) ___  _   _  ___ _   _ _ __  | |__ | | __ _ _ __   ___ "<<endl;
				cout <<"//    | |/ _ \\| | | |/ _ | | | | '__| | '_ \\| |/ _` | '_ \\ / __|"<<endl;
				cout <<"//    | | (_) | |_| |  __| |_| | |    | |_) | | (_| | | | | (__ "<<endl;
				cout <<"//   _/ |\\___/ \\__,_|\\___|\\__,_|_|    |_.__/|_|\\__,_|_| |_|\\___|"<<endl;
				cout <<"//  |__/                                                        "<<endl;

			}
		}else{
			partie=false;
			cout <<"__________  ________________"<<endl;
			cout <<"\\______   \\/  _  \\__    ___/"<<endl;
			cout <<" |     ___/  /_\\  \\|    |   "<<endl;
			cout <<" |    |  /    |    \\    |   "<<endl;
			cout <<" |____|  \\____|__  /____|   "<<endl;
			cout <<"                 \\/         "<<endl;
		}
		cout <<"tour joueur noire" << endl ;
		if(partie){
			if(!isPat(&jb, &jn,&e)){
				if (!isJoueurMAT(&jn, &jb,&e)){
					cout <<" _ _ _    _   _   _ _ _   "<<endl;
					cout <<"|_   _| / _ \\| | | | _ \\  "<<endl;
					cout <<"  | |  | (_) | |_| |   /  "<<endl;
					cout <<"  |_|   \\___/ \\___/|_|_\\  "<<endl;
					cout <<"                       "<<endl;
					cout <<"//      _                                           _      "<<endl;
					cout <<"//     (_)                                         (_)     "<<endl;
					cout <<"//      _  ___  _   _  ___ _   _ _ __   _ __   ___  _ _ __ "<<endl;
					cout <<"//     | |/ _ \\| | | |/ _ | | | | '__| | '_ \\ / _ \\| | '__|"<<endl;
					cout <<"//     | | (_) | |_| |  __| |_| | |    | | | | (_) | | |   "<<endl;
					cout <<"//     | |\\___/ \\__,_|\\___|\\__,_|_|    |_| |_|\\___/|_|_|   "<<endl;
					cout <<"//    _/ |                                                 "<<endl;
					cout <<"//   |__/                                                  "<<endl;

					tour(&jn, &jb,&e);
				}else{
					partie=false;
					cout <<" _______  _______  _______  _______    _______           _______  _______ "<<endl;
					cout <<"(  ____ \\(  ___  )(       )(  ____ \\  (  ___  )|\\     /|(  ____ \\(  ____ )"<<endl;
					cout <<"| (    \\/| (   ) || () () || (    \\/  | (   ) || )   ( || (    \\/| (    )|"<<endl;
					cout <<"| |      | (___) || || || || (__      | |   | || |   | || (__    | (____)|"<<endl;
					cout <<"| | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)"<<endl;
					cout <<"| | \\_  )| (   ) || |   | || (        | |   | | \\ \\_/ / | (      | (\\ (   "<<endl;
					cout <<"| (___) || )   ( || )   ( || (____/\\  | (___) |  \\   /  | (____/\\| ) \\ \\__"<<endl;
					cout <<"(_______)|/     \\||/     \\|(_______/  (_______)   \\_/   (_______/|/   \\__/"<<endl;
					cout <<"      _____                                ______        _            "<<endl;
					cout <<"	 (_____)                              |  ___ \\      (_)           "<<endl;
					cout <<"	    _  ___  _   _  ____ _   _  ____   | |   | | ___  _  ____ ____ "<<endl;
					cout <<"	   | |/ _ \\| | | |/ _  | | | |/ ___)  | |   | |/ _ \\| |/ ___/ _  )"<<endl;
					cout <<"	___| | |_| | |_| ( (/ /| |_| | |      | |   | | |_| | | |  ( (/ / "<<endl;
					cout <<"   (____/ \\___/ \\____|\\____)\\____|_|      |_|   |_|\\___/|_|_|   \\____)"<<endl;

				}
			}else{
				partie=false;
				cout <<"__________  ________________"<<endl;
				cout <<"\\______   \\/  _  \\__    ___/"<<endl;
				cout <<" |     ___/  /_\\  \\|    |   "<<endl;
				cout <<" |    |  /    |    \\    |   "<<endl;
				cout <<" |____|  \\____|__  /____|   "<<endl;
				cout <<"                 \\/         "<<endl;
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

	// les objets definis dans cette fonction sont automatiquement d�truits.
	// Ex : p1
}
