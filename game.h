#ifndef GAME_H
#define GAME_H

#include "board.h"

int IsOccupied(const GameState *game, int position);
int MovePiece(GameState *game, int from, int to);
int CheckWin(const GameState *game);

#endif