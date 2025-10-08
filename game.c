#include "game.h"
#include <stdio.h>
#include <stdlib.h>

static inline int row_of(int pos){ return pos / 8; }
static inline int col_of(int pos){ return pos % 8; }

int IsOccupied(const GameState *game, int position){
    if(position < 0 || position >= 64) return 0;
    unsigned long long all = game->red_pieces | game->red_kings | game->black_pieces | game->black_kings;
    return (int)((all >> position) & 1ULL);
}

int CheckWin(const GameState *game){
    if((game->red_pieces | game->red_kings) == 0) return 2; 
    if((game->black_pieces | game->black_kings) == 0) return 1; 
    return 0;
}

static int piece_has_capture(const GameState *game, int pos, int side){

    int r = row_of(pos), c = col_of(pos);
    unsigned long long own_kings = (side == 0) ? game->red_kings : game->black_kings;
    int is_king = ((own_kings >> pos) & 1ULL) ? 1 : 0;

    unsigned long long opp = (side == 0) ? (game->black_pieces | game->black_kings) : (game->red_pieces | game->red_kings);

    const int drs[4] = {1, 1, -1, -1};
    const int dcs[4] = {1, -1, 1, -1};

    for(int d = 0; d < 4; ++d){
        if(!is_king){
            if(side == 0 && drs[d] != 1) continue; 
            if(side == 1 && drs[d] != -1) continue;
        }
        int midr = r + drs[d], midc = c + dcs[d];
        int tr = r + 2*drs[d], tc = c + 2*dcs[d];
        if(midr < 0 || midr > 7 || midc < 0 || midc > 7) continue;
        if(tr < 0 || tr > 7 || tc < 0 || tc > 7) continue;
        int midpos = midr*8 + midc;
        int topos = tr*8 + tc;
        if(((opp >> midpos) & 1ULL) && !IsOccupied(game, topos)) return 1;
    }
    return 0;
}


static int any_capture_available(const GameState *game, int side){
    unsigned long long pieces = (side == 0) ? (game->red_pieces | game->red_kings) : (game->black_pieces | game->black_kings);
    for(int pos = 0; pos < 64; ++pos){
        if(((pieces >> pos) & 1ULL) && piece_has_capture(game, pos, side)) return 1;
    }
    return 0;
}

static void do_move_bits(GameState *game, int from, int to){
    unsigned long long from_mask = 1ULL << from;
    unsigned long long to_mask = 1ULL << to;

    if(game->red_pieces & from_mask){
        game->red_pieces &= ~from_mask;
        game->red_pieces |= to_mask;
    } else if(game->red_kings & from_mask){
        game->red_kings &= ~from_mask;
        game->red_kings |= to_mask;
    } else if(game->black_pieces & from_mask){
        game->black_pieces &= ~from_mask;
        game->black_pieces |= to_mask;
    } else if(game->black_kings & from_mask){
        game->black_kings &= ~from_mask;
        game->black_kings |= to_mask;
    }
}

static void remove_piece_at(GameState *game, int pos){
    unsigned long long m = ~(1ULL << pos);
    game->red_pieces &= m;
    game->red_kings  &= m;
    game->black_pieces &= m;
    game->black_kings  &= m;
}


static void promote(GameState *game, int to){
    unsigned long long to_mask = 1ULL << to;
    int tr = row_of(to);

    if((game->red_pieces & to_mask) && tr == 7){
        game->red_pieces &= ~to_mask;
        game->red_kings  |= to_mask;
    }

    if((game->black_pieces & to_mask) && tr == 0){
        game->black_pieces &= ~to_mask;
        game->black_kings  |= to_mask;
    }
}

// Function to validate move and execute it if valid
int MovePiece(GameState *game, int from, int to){
    if(from < 0 || from >= 64 || to < 0 || to >= 64) return 0;
    if(from == to) return 0;
    if(IsOccupied(game, to)) return 0;

    int side = game->turn; 
    unsigned long long my_men = (side == 0) ? game->red_pieces : game->black_pieces;
    unsigned long long my_kings = (side == 0) ? game->red_kings : game->black_kings;
    unsigned long long my_all = my_men | my_kings;

    if(!((my_all >> from) & 1ULL)) return 0; 

    int fr = row_of(from), fc = col_of(from);
    int tr = row_of(to), tc = col_of(to);
    int dr = tr - fr, dc = tc - fc;
    int adr = dr >= 0 ? dr : -dr;
    int adc = dc >= 0 ? dc : -dc;

    if(adr != adc) return 0; 

    int is_king = ((my_kings >> from) & 1ULL) ? 1 : 0;

    // If any capture available, simple steps are not allowed
    int capture_exists = any_capture_available(game, side);

    // Single-step move
    if(adr == 1 && adc == 1){
        if(capture_exists) return 0; 
        if(!is_king){
            if(side == 0 && dr != 1) return 0; 
            if(side == 1 && dr != -1) return 0; 
        }
        do_move_bits(game, from, to);
        maybe_promote(game, to);
        game->turn ^= 1;
        return 1;
    }

    
    if(adr == 2 && adc == 2){
        int midr = (fr + tr) / 2;
        int midc = (fc + tc) / 2;
        int midpos = midr*8 + midc;
        unsigned long long opp_all = (side == 0) ? (game->black_pieces | game->black_kings) : (game->red_pieces | game->red_kings);
        if(!((opp_all >> midpos) & 1ULL)) return 0; 
        if(!is_king){
            if(side == 0 && dr != 2) return 0;
            if(side == 1 && dr != -2) return 0;
        }

        do_move_bits(game, from, to);
        remove_piece_at(game, midpos);
        maybe_promote(game, to);

        // Checks for multi capture moves and automatically executes secondary captures
        int cont_pos = to;
        while(piece_has_capture(game, cont_pos, side)){
            int r = row_of(cont_pos), c = col_of(cont_pos);
            int performed = 0;
            unsigned long long opp = (side == 0) ? (game->black_pieces | game->black_kings) : (game->red_pieces | game->red_kings);
            int is_k = (( (side==0 ? game->red_kings : game->black_kings) >> cont_pos) & 1ULL) ? 1 : 0;

            const int drs[4] = {1, 1, -1, -1};
            const int dcs[4] = {1, -1, 1, -1};

            for(int d = 0; d < 4 && !performed; ++d){
                if(!is_k){
                    if(side == 0 && drs[d] != 1) continue;
                    if(side == 1 && drs[d] != -1) continue;
                }
                int midr2 = r + drs[d];
                int midc2 = c + dcs[d];
                int tr2 = r + 2*drs[d];
                int tc2 = c + 2*dcs[d];
                if(midr2 < 0 || midr2 > 7 || midc2 < 0 || midc2 > 7) continue;
                if(tr2 < 0 || tr2 > 7 || tc2 < 0 || tc2 > 7) continue;
                int midp = midr2*8 + midc2;
                int top = tr2*8 + tc2;
                if(((opp >> midp) & 1ULL) && !IsOccupied(game, top)){
                    do_move_bits(game, cont_pos, top);
                    remove_piece_at(game, midp);
                    maybe_promote(game, top);
                    cont_pos = top;
                    performed = 1;
                }
            }
            if(!performed) break;
        }

        game->turn ^= 1;
        return 1;
    }

    return 0;
}

bool MakeMove(GameState* game, int from, int to){
    return MovePiece(game, from, to) ? true : false;
}
