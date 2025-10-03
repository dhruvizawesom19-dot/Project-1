#include "game.h"

int IsOccupied(const GameState *game, int position){
    unsigned long long all = game->red_pieces | game->black_pieces | game->red_kings | game->black_kings;
    return (all >> position) & 1ULL;
}

