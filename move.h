#ifndef ___MOVE_H___
#define ___MOVE_H___

#include "field.h"

#include <stdbool.h>

#define UP (0)
#define RIGHT (1)
#define DOWN (2)
#define LEFT (3)

typedef struct _MOVE {
    int col;
    int dir;
    int occupations[2];
} MOVE;

extern MOVE COL_1_DIR_U;
extern MOVE COL_1_DIR_R;
extern MOVE COL_1_DIR_D;
extern MOVE COL_2_DIR_U;
extern MOVE COL_2_DIR_R;
extern MOVE COL_2_DIR_D;
extern MOVE COL_2_DIR_L;
extern MOVE COL_3_DIR_U;
extern MOVE COL_3_DIR_R;
extern MOVE COL_3_DIR_D;
extern MOVE COL_3_DIR_L;
extern MOVE COL_4_DIR_U;
extern MOVE COL_4_DIR_R;
extern MOVE COL_4_DIR_D;
extern MOVE COL_4_DIR_L;
extern MOVE COL_5_DIR_U;
extern MOVE COL_5_DIR_R;
extern MOVE COL_5_DIR_D;
extern MOVE COL_5_DIR_L;
extern MOVE COL_6_DIR_U;
extern MOVE COL_6_DIR_D;
extern MOVE COL_6_DIR_L;

extern MOVE ALL_MOVES[];

#define print_move(move) printf("<MOVE col=%d, dir=%d, occupation=[%d, %d]>\n", move.col, move.dir, move.occupations[0], move.occupations[1]);

void init_moves();
int move_patterns(MOVE **patterns, bool no_chigiri, int heights[MAX_COL], bool for_double);

typedef struct _MOVE_NODE {
    struct _MOVE_NODE *parent;
    MOVE moves[256];
    int moves_size;
    int heights[MAX_COL];
    int child_ids[22];
} MOVE_NODE;

void print_moves(MOVE *moves, int size);

int next_move_patterns(MOVE_NODE **children, MOVE_NODE *parent, bool no_chigiri, bool for_double);

int one_depth_patterns(MOVE_NODE **children, MOVE_NODE **parents, bool no_chigiri, bool for_double);

int all_depth_patterns(int depth, bool no_chigiri, int initial_heights[6], char *for_pattern);

#endif//___MOVE_H___
