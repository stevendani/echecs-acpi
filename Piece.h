/**
 * Header de Piece.cxx
 *
 * @file Piece.h
 */
#if !defined Piece_h
#define Piece_h
#include <vector>
using namespace std;
//#include "Echiquier.h"
class Echiquier;

/**
 * Declaration d'une classe mod�lisant une piece de jeu d'echec.
 */
class Piece
{
protected:
  int m_x;
  int m_y;
  bool m_white;

public:
  Piece();
  virtual ~Piece();
  Piece(const Piece & autre);
  Piece & operator=(const Piece & autre);
  Piece( int x, int y, bool white );
  void init( int x, int y, bool white );
  void move( int x, int y );
  int x();
  int y();
  bool isWhite();
  bool isBlack();
  void affiche();
  char getPosition();
  virtual bool mouvementValide(Echiquier* e, int x, int y);
  virtual vector<int*> getMouvementsPossibles(Echiquier* e)=0;
  virtual char codePiece();
};

class Roi : public Piece
{
 public:
  Roi(bool white);
  bool mouvementValide(Echiquier* e, int x, int y);
  vector<int*> getMouvementsPossibles(Echiquier* e);
  char codePiece();
};

class Fou : virtual public Piece
{
 public:
  Fou(bool white, bool left);
  Fou(bool white, int x, int y);
  bool mouvementValide(Echiquier* e, int x, int y);
  vector<int*> getMouvementsPossibles(Echiquier* e);
  char codePiece();
};

class Cavalier : virtual public Piece
{
 public:
  Cavalier(bool white, bool left);
  Cavalier(bool white, int x, int y);
  bool mouvementValide(Echiquier* e, int x, int y);
  vector<int*> getMouvementsPossibles(Echiquier* e);
  char codePiece();
};

class Tour : virtual public Piece
{
 public:
  Tour(bool white, bool left);
  Tour(bool white, int x, int y);
  bool mouvementValide(Echiquier* e, int x, int y);
  vector<int*> getMouvementsPossibles(Echiquier* e);
  char codePiece();
};

class Pion : virtual public Piece
{
 public:
  Pion(bool white, int pos);
  bool mouvementValide(Echiquier* e, int x, int y);
  vector<int*> getMouvementsPossibles(Echiquier* e);
  char codePiece();
};

class Reine : public Tour, public Fou
{
 public:
  Reine(bool white);
  Reine(bool white, int x, int y);
  bool mouvementValide(Echiquier* e, int x, int y);
  vector<int*> getMouvementsPossibles(Echiquier* e);
  char codePiece();
};

#endif // !defined Piece_h
