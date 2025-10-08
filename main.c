#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "board.h"
#include "game.h"


int coordToPos(char file, int rank){
    if(!isalpha((unsigned char)file)) return -1;
    int col = toupper((unsigned char)file) - 'A';
    int r = rank - 1;
    if(col < 0 || col > 7) return -1;
    if(r < 0 || r > 7) return -1;
    return r * 8 + col;
}

int main(void){
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
        char ffile=0, tfile=0;
        int frank=0, trank=0;
        if(scanf(" %c%d %c%d", &ffile, &frank, &tfile, &trank) != 4){
            printf("Invalid input format. Use like: A3 B4\n");
            while(getchar() != '\n'); // flush
            continue;
        }

        int from = coordToPos(ffile, frank);
        int to   = coordToPos(tfile, trank);
        if(from < 0 || to < 0){
            printf("Coordinates out of range. Use A1..H8\n");
            continue;
        }

        if(!MakeMove(&game, from, to)){
            printf("Invalid move. Try again.\n");
        }
    }
    return 0;
}
