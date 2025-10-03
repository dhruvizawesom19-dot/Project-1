#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void InitializeBoard(GameState *game){
    game->red_pieces = 0x00000000000FFF00ULL;
    game->black_pieces = 0x00FFF00000000000ULL;
    game->red_kings = 0ULL;
    game->black_kings = 0ULL;
    game->turn = 0;
}

void PrintBoard(const GameState *game){
   
}