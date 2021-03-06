/**
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

#include <stdlib.h>
#include <iostream>
// A besoin de la declaration de la classe
#include "Piece.h"
#include "Echiquier.h"

using namespace std;

Piece::Piece()
{
}

Piece::Piece(const Piece & autre)
{
	m_x=autre.m_x;
	m_y=autre.m_y;
	m_white=autre.m_white;
}

Piece &
Piece::operator=(const Piece & autre)
{
	m_x=autre.m_x;
	m_y=autre.m_y;
	m_white=autre.m_white;
	return *this;
}

Piece::~Piece()
{
}

Piece::Piece( int x, int y, bool white )
{
	m_x = x;
	m_y = y;
	m_white = white;
}

void
Piece::init( int x, int y, bool white )
{
	m_x = x;
	m_y = y;
	m_white = white;
}

void
Piece::move( int x, int y )
{
	m_x = x;
	m_y = y;
}

int
Piece::x()
{
	return m_x;
}

int
Piece::y()
{
	return m_y;
}

bool
Piece::isWhite()
{
	return m_white;
}


bool
Piece::isBlack()
{
	return !m_white;
}

void
Piece::affiche()
{
	cout << "Piece: x=" << m_x << " y=" << m_y << " "
			<< ( m_white ? "blanche" : "noire" ) << endl;
}

bool
Piece::mouvementValide(Echiquier* e, int x, int y)
{
	if(x>=1 && x<=8 && y>=1 && y<=8){
		if(e->getPiece(x,y)){
			if(e->getPiece(x,y)->m_white == m_white){
				return false;
			}
		}
		return true;
	}
	return false;
}

char
Piece::codePiece()
{
	return (m_white)?'B':'N';
}

char
Piece::getPosition()
{
	char x;
	char y;
	x=m_x;
	y=m_y;
	return x+y;
}

//=====FIN PIECE=====\\
//==========================================================\\
//=====ROI=====\\

Roi::Roi(bool white)
{
	m_x=5;
	m_y=white?1:8;
	m_white=white;
}

bool
Roi::mouvementValide(Echiquier* e, int x, int y)
{
	if(Piece::mouvementValide(e,x,y)){
		if((abs(x-m_x)<=1) && (abs(y-m_y)<=1) && (x!=m_x || y!=m_y)){
			return true;
		}
	}
	return false;
}

vector<int*>
Roi::getMouvementsPossibles(Echiquier* e){
	vector<int*> ret;
	for (int i=-1; i<=1;i++){
		for (int j=-1; j<=1; j++){
			if (mouvementValide(e,m_x+i,m_y+j) && !(i==0 && j==0)){
				int* tab = new int[2]();
				tab[0]=m_x+i;
				tab[1]=m_y+j;
				ret.push_back(tab);
			}
		}
	}
	return ret;
}

char
Roi::codePiece()
{
	return (m_white)?'R':'r';
}

//=====FIN ROI=====\\
//==========================================================\\
//=====REINE=====\\

Reine::Reine(bool white) : Piece(4,white?1:8,white), Fou(white,true), Tour(white,true)
{
}
Reine::Reine(bool white, int x, int y) : Piece(x, y,white), Fou(white,true), Tour(white,true)
{

}
bool
Reine::mouvementValide(Echiquier* e, int x, int y)
{
	return Fou::mouvementValide(e,x,y) || Tour::mouvementValide(e,x,y);
}

vector<int*>
Reine::getMouvementsPossibles(Echiquier* e){
	vector<int*> ret=Fou::getMouvementsPossibles(e);
	vector<int*> tmp=Tour::getMouvementsPossibles(e);
	ret.insert(ret.end(), tmp.begin(), tmp.end());
	return ret;
}

char
Reine::codePiece()
{
	return (m_white)?'Q':'q';
}

//=====FIN REINE=====\\
//==========================================================\\
//=====TOUR=====\\

Tour::Tour(bool white, bool left) : Piece(left?1:8, white?1:8,white)
{
}
Tour::Tour(bool white, int x, int y) : Piece(x, y,white)
{
}

bool
Tour::mouvementValide(Echiquier* e, int x, int y)
{
	if(Piece::mouvementValide(e,x,y)){
		if((x == m_x && y != m_y)||(x != m_x && y == m_y)){
			if(y == m_y){
				for(int i=min(x,m_x)+1;i<max(x,m_x);i++){
					if(e->getPiece(i, y)){
						return false;
					}
				}
				return true;
			}
			else if(x == m_x){
				for(int i=min(y,m_y)+1;i<max(y,m_y);i++){
					if(e->getPiece(x, i)){
						return false;
					}
				}
				return true;
			}
		}
	}
	return false;
}

vector<int*>
Tour::getMouvementsPossibles(Echiquier* e){
	vector<int*> ret;
	for( int i=1; i<=8; i++){
		if(mouvementValide(e,m_x,i)){
			int* tab = new int[2]();
			tab[0]=m_x;
			tab[1]=i;
			ret.push_back(tab);
		}
		if(mouvementValide(e,i,m_y)){
			int* tab = new int[2]();
			tab[0]=i;
			tab[0]=m_y;
			ret.push_back(tab);
		}
	}
	return ret;
}

char
Tour::codePiece()
{
	return (m_white)?'T':'t';
}

//=====FIN TOUR=====\\
//==========================================================\\
//=====FOU=====\\

Fou::Fou(bool white, bool left) : Piece(left?3:6, white?1:8,white)
{
}
Fou::Fou(bool white, int x, int y) : Piece(x, y,white)
{

}
bool
Fou::mouvementValide(Echiquier* e, int x, int y)
{
	if(Piece::mouvementValide(e,x,y)){
		if((abs(x-m_x))==(abs(y-m_y)) ){
			int axeY=0;
			int incr=0;
			if(x<m_x){
				axeY=y;
				if (y<m_y){
					incr=1;
				}else{
					incr=-1;
				}
			}else{
				axeY=m_y;
				if (y<m_y){
					incr=-1;
				}else{
					incr=1;
				}
			}

			for(int i=min(x,m_x)+1;i<max(x,m_x);i++){
				axeY=axeY+incr;
				if(e->getPiece(i,axeY)){
					return false;
				}
			}

			return true;
		}
	}
	return false;
}

vector<int*>
Fou::getMouvementsPossibles(Echiquier* e){
	vector<int*> ret;
	for(int i=1; i<=7; i++){
		if(mouvementValide(e,m_x+i,m_y+i)){
			int* tab = new int[2]();
			tab[0]=m_x+i;
			tab[1]=m_y+i;
			ret.push_back(tab);
		}
		if(mouvementValide(e,m_x-i,m_y-i)){
			int* tab = new int[2]();
			tab[0]=m_x-i;
			tab[1]=m_y-i;
			ret.push_back(tab);
		}
		if(mouvementValide(e,m_x-i,m_y+i)){
			int* tab = new int[2]();
			tab[0]=m_x-i;
			tab[1]=m_y+i;
			ret.push_back(tab);
		}
		if(mouvementValide(e,m_x+i,m_y-i)){
			int* tab = new int[2]();
			tab[0]=m_x+i;
			tab[1]=m_y-i;
			ret.push_back(tab);
		}
	}
	return ret;

}

char
Fou::codePiece()
{
	return (m_white)?'F':'f';
}

//=====FIN FOU=====\\
//==========================================================\\
//=====CAVALIER=====\\

Cavalier::Cavalier(bool white, bool left) : Piece(left?2:7, white?1:8,white)
{
}
Cavalier::Cavalier(bool white, int x, int y) : Piece(x, y,white)
{

}
bool
Cavalier::mouvementValide(Echiquier* e, int x, int y)
{
	if(Piece::mouvementValide(e,x,y)){
		if( ( (abs(x-m_x)==2) && (abs(y-m_y)==1) ) || ( (abs(x-m_x)==1) && (abs(y-m_y)==2) ) ){
			return true;
		}
	}
	return false;
}

vector<int*>
Cavalier::getMouvementsPossibles(Echiquier* e){
	vector <int*> ret;
	for (int i=1; i<=2; i++){
		if (mouvementValide(e,m_x+(i%2)+1,m_y+((i+1)%2)+1)){
			int* tab = new int[2]();
			tab[0]=m_x+(i%2)+1;
			tab[1]=m_y+((i+1)%2)+1;
			ret.push_back(tab);
		}
		if (mouvementValide(e,m_x-(i%2)-1,m_y+((i+1)%2)+1)){
			int* tab = new int[2]();
			tab[0]=m_x-(i%2)-1;
			tab[1]=m_y+((i+1)%2)+1;
			ret.push_back(tab);
		}
		if (mouvementValide(e,m_x+(i%2)+1,m_y-((i+1)%2)-1)){
			int* tab = new int[2]();
			tab[0]=m_x+(i%2)+1;
			tab[1]=m_y-((i+1)%2)-1;
			ret.push_back(tab);
		}
		if (mouvementValide(e,m_x-(i%2)-1,m_y-((i+1)%2)-1)){
			int* tab = new int[2]();
			tab[0]=m_x-(i%2)-1;
			tab[1]=m_y-((i+1)%2)-1;
			ret.push_back(tab);
		}
	}
	return ret;
}

char
Cavalier::codePiece()
{
	return (m_white)?'C':'c';
}

//=====FIN CAVALIER=====\\
//==========================================================\\
//=====PION=====\\

Pion::Pion(bool white, int pos) : Piece(pos, white?2:7,white)
{
}

bool
Pion::mouvementValide(Echiquier* e, int x, int y)
{
	if(Piece::mouvementValide(e,x,y)){
		if((m_white && x==m_x && y == 4 && m_y==2 && e->getPiece(m_x, 3)==NULL && e->getPiece(m_x, 4)==NULL) || ((!m_white)&& x==m_x  && y == 5 && m_y==7 && e->getPiece(m_x, 6)==NULL && e->getPiece(m_x, 5)==NULL)){
			return true;
		} else if((m_white && y == m_y+1 && abs(x-m_x)<=1) || ((!m_white) && y == m_y-1 && abs(x-m_x)<=1)){
			if(abs(x-m_x)==1){
				if(e->getPiece(x,y)!= NULL){
					if(e->getPiece(x,y)->isWhite() != m_white){
						return true;
					}
				}
				return false;
			}
			if(e->getPiece(x,y)==NULL){return true;}
		}
	}
	return false;
}

vector<int*>
Pion::getMouvementsPossibles(Echiquier* e){
	vector <int*> ret;
	int mult = isWhite()?1:-1;
	if (mouvementValide(e,m_x,m_y+(2*mult))){
		int* tab = new int[2]();
		tab[0]=m_x;
		tab[1]=m_y+(2*mult);
		ret.push_back(tab);
	}
	if (mouvementValide(e,m_x,m_y+mult)){
		int* tab = new int[2]();
		tab[0]=m_x;
		tab[1]=m_y+mult;
		ret.push_back(tab);
	}
	if(mouvementValide(e,m_x+1,m_y+mult)){
		int* tab = new int[2]();
		tab[0]=m_x+1;
		tab[1]=m_y+mult;
		ret.push_back(tab);
	}
	if(mouvementValide(e,m_x-1,m_y+mult)){
		int* tab = new int[2]();
		tab[0]=m_x-1;
		tab[1]=m_y+mult;
		ret.push_back(tab);
	}
	return ret;
}

char
Pion::codePiece()
{
	return (m_white)?'P':'p';
}

//=====FIN PION=====\\
//==========================================================\\

