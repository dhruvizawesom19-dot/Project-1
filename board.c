#include "board.h"
#include <stdio.h>
// Create a new game state with pieces in starting positions
void InitializeBoard(GameState *game){

    game->red_pieces = 0ULL;
    game->black_pieces = 0ULL;
    game->red_kings = 0ULL;
    game->black_kings = 0ULL;
    game->turn = 0; 

    for(int r = 0; r < 8; ++r){
        for(int c = 0; c < 8; ++c){
            if(((r + c) & 1) == 1){
                int pos = r * 8 + c;
                if(r <= 2) game->red_pieces |= (1ULL << pos);
                else if(r >= 5) game->black_pieces |= (1ULL << pos);
            }
        }
    }
}

void PrintBoard(const GameState *game){
    printf("\n   A B C D E F G H\n");
    for(int row = 7; row >= 0; --row){
        printf("%d  ", row + 1);
        for(int col = 0; col < 8; ++col){
            int pos = row * 8 + col;
            unsigned long long mask = 1ULL << pos;
            char ch = '.';
            if(game->red_kings & mask) ch = 'R';
            else if(game->red_pieces & mask) ch = 'r';
            else if(game->black_kings & mask) ch = 'B';
            else if(game->black_pieces & mask) ch = 'b';
            printf("%c ", ch);
        }
        printf("%d\n", row + 1);
    }
    printf("   A B C D E F G H\n\n");
}
