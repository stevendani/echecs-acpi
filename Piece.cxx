/** 
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

// A besoin de la declaration de la classe
#include <iostream>
#include "Piece.h"

using namespace std;

Piece::Piece()
{
  cout << "DEBUG : Constructeur Piece defaut" << endl;
}

Piece::Piece(const Piece & autre)
{
  m_x=autre.m_x;
  m_y=autre.m_y;
  m_white=autre.m_white;
  cout << "DEBUG : Constructeur Piece par copie" << endl;
}

Piece &
Piece::operator=(const Piece & autre)
{
  m_x=autre.m_x;
  m_y=autre.m_y;
  m_white=autre.m_white;
  cout << "DEBUG : Affectation Piece" << endl;
  return *this;
}

Piece::~Piece()
{
  cout << "DEBUG : Destructeur Piece" << endl;
}

Piece::Piece( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
  cout << "DEBUG : Constructeur Piece specialise" << endl;
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
Piece::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "DEBUG : mouvementValide Piece" << endl;
  return false;
}

char
Piece::codePiece()
{
  return (m_white)?'B':'N';
}

//==========================================================\\

Roi::Roi(bool white)
{
  m_x=5;
  m_y=white?1:8;
  m_white=white;
  cout << "DEBUG : Constructeur Roi" << endl;
}

bool
Roi::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "DEBUG : mouvementValide Roi" << endl;
  return false;
}

char
Roi::codePiece()
{
  return (m_white)?'R':'r';
}

//==========================================================\\

Reine::Reine(bool white) : Piece(4,white?1:8,white), Fou(white,true), Tour(white,true)
{
  cout << "DEBUG : Constructeur Reine" << endl;
}

bool
Reine::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "DEBUG : mouvementValide Reine" << endl;
  return Fou::mouvementValide(e,x,y) || Tour::mouvementValide(e,x,y);
}

char
Reine::codePiece()
{
  return (m_white)?'Q':'q';
}

//==========================================================\\

Tour::Tour(bool white, bool left) : Piece(left?1:8, white?1:8,white)
{
  cout << "DEBUG : Constructeur Tour" << endl;
}

bool
Tour::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "DEBUG : mouvementValide Tour" << endl;
  return false;
}

char
Tour::codePiece()
{
  return (m_white)?'T':'t';
}

//==========================================================\\

Fou::Fou(bool white, bool left) : Piece(left?3:6, white?1:8,white)
{
  cout << "DEBUG : Constructeur Fou" << endl;
}

bool
Fou::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "DEBUG : mouvementValide Fou" << endl;
  return false;
}

char
Fou::codePiece()
{
  return (m_white)?'F':'f';
}
