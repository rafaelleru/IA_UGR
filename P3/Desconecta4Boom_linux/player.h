#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player{
    public:
      Player(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
    /*  int cuenta4Hor(Environment &tablero, int player);
      int cuenta3Hor(Environment &tablero, int player);
      int cuenta2Hor(Environment &tablero, int player);
      int cuenta4Vert(Environment &tablero, int player);
      int cuenta3Vert(Environment &tablero, int player);
      int cuenta2Vert(Environment &tablero, int player);
      int cuenta4Diag(Environment &tablero, int player);
      int cuenta3Diag(Environment &tablero, int player);
      int cuenta2Diag(Environment &tablero, int player);*/


    private:
      int LIMITE_PODA;
      int jugador_;
      Environment actual_;
};
#endif
