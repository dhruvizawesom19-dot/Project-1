#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "board.h"

bool MakeMove(GameState* game, int from, int to);

int IsOccupied(const GameState *game, int position);
int MovePiece(GameState *game, int from, int to); 
int CheckWin(const GameState *game);

#endif
