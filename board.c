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
   printf("\n   A B C D E F G H\n");
    for (int row = 7; row >= 0; row--) {
        printf("%d  ", row + 1);
        for (int col = 0; col < 8; col++) {
            int pos = row * 8 + col;
            unsigned long long mask = 1ULL << pos;

            char symbol = '.';
            if (game->red_pieces & mask) symbol = 'r';
            if (game->black_pieces & mask) symbol = 'b';
            if (game->red_kings & mask) symbol = 'R';
            if (game->black_kings & mask) symbol = 'B';

            printf("%c ", symbol);
        }
        printf("%d\n", row + 1);
    }
    printf("   A B C D E F G H\n\n");
}