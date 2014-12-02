#include <iostream>
#include "Joueur.h"

using namespace std;

Joueur::Joueur()
{
  cout << "DEBUG : Constructeur Joueur defaut" << endl;
}

Joueur::~Joueur()
{
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      delete *p;
      p++;
    }
  cout << "DEBUG : Destructeur Joueur" << endl;
}

Joueur::Joueur(bool white)
{
  /*
  int n = 0;
  int y = white ? 1 : 8;
  for ( int x = 1; x <= 8; ++x )
    m_pieces[ n++ ].init( x, y, white );
  y = white ? 2 : 7;
  for ( int x = 1; x <= 8; ++x )
    m_pieces[ n++ ].init( x, y, white );
  cout << "Constructeur Joueur specialise" << endl;
  */
}

void 
Joueur::affiche()
{
  /*
  for (int i=0; i<16; i++)
    m_pieces[i].affiche();
  */
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      (*p)->affiche();
      p++;
    }
}

bool
Joueur::isWhite()
{
  return m_pieces[0]->isWhite();
}

void
Joueur::placerPieces(Echiquier &e)
{
  /*
  for (int i=0; i<16; i++)
    e.placer(&(m_pieces[i]));
  */
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      e.placer(*p);
      p++;
    }
}

JoueurBlanc::JoueurBlanc() //: Joueur(true)
{
  cout << "DEBUG : Constructeur Joueur Blanc" << endl;
  Roi* rb = new Roi(true);
  Reine* qb = new Reine(true);
  Fou* fbl = new Fou(true,true);
  Fou* fbr = new Fou(true,false);
  Tour* tbl = new Tour(true,true);
  Tour* tbr = new Tour(true,false);
  m_pieces.push_back(rb);
  m_pieces.push_back(qb);
  m_pieces.push_back(fbl);
  m_pieces.push_back(fbr);
  m_pieces.push_back(tbl);
  m_pieces.push_back(tbr);
  
  for(int i=1; i<=8; i++){
		Piece* p = new Piece(i, 2, true);
		m_pieces.push_back(p);
  }
}

JoueurNoir::JoueurNoir() //: Joueur(false)
{
  cout << "DEBUG : Constructeur Joueur Noir" << endl;
  Roi* rn = new Roi(false);
  Reine* qn = new Reine(false);
  Fou* fnl = new Fou(false,true);
  Fou* fnr = new Fou(false,false);
  Tour* tnl = new Tour(false,true);
  Tour* tnr = new Tour(false,false);
  m_pieces.push_back(rn);
  m_pieces.push_back(qn);
  m_pieces.push_back(fnl);
  m_pieces.push_back(fnr);
  m_pieces.push_back(tnl);
  m_pieces.push_back(tnr);
  
for(int i=1; i<=8; i++){
	Piece* p = new Piece(i, 7, false);
	m_pieces.push_back(p);
  }
}
