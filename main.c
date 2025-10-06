#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "board.h"
#include "game.h"



int coordToPos(char file, int rank){
    if(!isalpha((unsigned char)file)) return -1;
    int col = toupper((unsigned char)file) - 'A';
    int r = rank;
    if(col < 0 || col > 7) return -1;
    if(r < 1 || r > 8) return -1;
    int row = 8 - r; // flip
    return row * 8 + col;
}

int main(){
    GameState game;
    InitializeBoard(&game);

    while(1){
        PrintBoard(&game);

        int winner = CheckWin(&game);
        if(winner == 1){
            printf("Red wins!\n");
            break;
        } else if(winner == 2){
            printf("Black wins!\n");
            break;
        }

        printf("%s's turn. Enter move (e.g., A3 B4): ", game.turn == 0 ? "Red" : "Black");

        char fromFile = 0, toFile = 0;
        int fromRank = 0, toRank = 0;
        if(scanf(" %c%d %c%d", &fromFile, &fromRank, &toFile, &toRank) != 4){
            printf("Invalid input format. Try again.\n");
            while(getchar() != '\n'); // clear remainder
            continue;
        }

        int from = coordToPos(fromFile, fromRank);
        int to   = coordToPos(toFile, toRank);

        if(from < 0 || to < 0){
            printf("Coordinates out of range. Use files A-H and ranks 1-8.\n");
            continue;
        }

        if(!MakeMove(&game, from, to)){
            printf("Invalid move. Try again.\n");
        }
    }
    return 0;
}
