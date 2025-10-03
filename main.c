#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"
#include "game.h"

int coordToPos(char file, int rank){
    int col = file - 'A';
    int row = rank - 1;
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

        char fromFile, toFile;
        int fromRank, toRank;
        if(scanf(" %c%d %c%d", &fromFile, &fromRank, &toFile, &toRank) != 4){
            printf("Invalid input format. Try again.\n");
            while(getchar() != '\n');
            continue;
        }
        int from = coordToPos(fromFile, fromRank);
        int to = coordToPos(toFile, toRank);

        if(!MakeMove(&game, from, to)){
            printf("Invalid move. Try again.\n");
        }
    }
    return 0;
}