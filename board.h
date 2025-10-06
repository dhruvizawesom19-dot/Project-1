#ifndef BOARD_H
#define BOARD_H

typedef struct {
    unsigned long long red_pieces; 
    unsigned long long black_pieces; 
    unsigned long long red_kings; 
    unsigned long long black_kings; 
    int turn; 
} GameState;

void InitializeBoard(GameState *game);
void PrintBoard(const GameState *game);

#endif
