#include "game.h"

int IsOccupied(const GameState *game, int position){
    unsigned long long all = game->red_pieces | game->black_pieces | game->red_kings | game->black_kings;
    return (all >> position) & 1ULL;
}

int MovePiece(GameState *game, int from, int to){
    unsigned long long from_pos = 1ULL << from;
    unsigned long long to_pos = 1ULL << to;

    if(IsOccupied(game, to)){
        return 0;
    }
    if(game->turn == 0){
        if(game->red_pieces & from_pos){
            game->red_pieces &= ~from_pos;
            game->red_pieces |= to_pos;
        } else if(game->red_kings & from_pos){
            game->red_kings &= ~from_pos;
            game->red_kings |= to_pos;
        } else {
            return 0;
        }
    } else {
        if(game->black_pieces & from_pos){
            game->black_pieces &= ~from_pos;
            game->black_pieces |= to_pos;
        } else if(game->black_kings & from_pos){
            game->black_kings &= ~from_pos;
            game->black_kings |= to_pos;
        } else {
            return 0;
        }
    }
    game->turn ^= 1;
    return 1;
}

int CheckWin(const GameState *game){
    if((game->red_pieces | game->red_kings) == 0){
        return 2; 
    }
    if((game->black_pieces | game->black_kings) == 0){
        return 1;
    }
    return 0;
}