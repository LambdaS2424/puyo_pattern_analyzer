#include "puyo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

MOVE COL_0_DIR_U = { 0, UP, 0, 0 };
MOVE COL_0_DIR_R = { 0, RIGHT, 0, 1 };
MOVE COL_0_DIR_D = { 0, DOWN, 0, 0 };
MOVE COL_1_DIR_U = { 1, UP, 1, 1 };
MOVE COL_1_DIR_R = { 1, RIGHT, 1, 2 };
MOVE COL_1_DIR_D = { 1, DOWN, 1, 1 };
MOVE COL_1_DIR_L = { 1, LEFT, 0, 1 };
MOVE COL_2_DIR_U = { 2, UP, 2, 2 };
MOVE COL_2_DIR_R = { 2, RIGHT, 2, 3 };
MOVE COL_2_DIR_D = { 2, DOWN, 2, 2 };
MOVE COL_2_DIR_L = { 2, LEFT, 2, 1 };
MOVE COL_3_DIR_U = { 3, UP, 3, 3 };
MOVE COL_3_DIR_R = { 3, RIGHT, 3, 4 };
MOVE COL_3_DIR_D = { 3, DOWN, 3, 3 };
MOVE COL_3_DIR_L = { 3, LEFT, 3, 2 };
MOVE COL_4_DIR_U = { 4, UP, 4, 4 };
MOVE COL_4_DIR_R = { 4, RIGHT, 4, 5 };
MOVE COL_4_DIR_D = { 4, DOWN, 4, 4 };
MOVE COL_4_DIR_L = { 4, LEFT, 4, 3 };
MOVE COL_5_DIR_U = { 5, UP, 5, 5 };
MOVE COL_5_DIR_D = { 5, DOWN, 5, 5 };
MOVE COL_5_DIR_L = { 5, LEFT, 5, 4 };

MOVE cp_move(MOVE from, MOVE *to) {
    to->col = from.col;
    to->dir = from.dir;
    to->occupations[0] = from.occupations[0];
    to->occupations[1] = from.occupations[1];

    return *to;
}

MOVE ALL_MOVES[22];

void init_moves() {
    cp_move(COL_0_DIR_U, &ALL_MOVES[0]);
    cp_move(COL_0_DIR_R, &ALL_MOVES[1]);
    cp_move(COL_0_DIR_D, &ALL_MOVES[2]);
    cp_move(COL_1_DIR_U, &ALL_MOVES[3]);
    cp_move(COL_1_DIR_R, &ALL_MOVES[4]);
    cp_move(COL_1_DIR_D, &ALL_MOVES[5]);
    cp_move(COL_1_DIR_L, &ALL_MOVES[6]);
    cp_move(COL_2_DIR_U, &ALL_MOVES[7]);
    cp_move(COL_2_DIR_R, &ALL_MOVES[8]);
    cp_move(COL_2_DIR_D, &ALL_MOVES[9]);
    cp_move(COL_2_DIR_L, &ALL_MOVES[10]);
    cp_move(COL_3_DIR_U, &ALL_MOVES[11]);
    cp_move(COL_3_DIR_R, &ALL_MOVES[12]);
    cp_move(COL_3_DIR_D, &ALL_MOVES[13]);
    cp_move(COL_3_DIR_L, &ALL_MOVES[14]);
    cp_move(COL_4_DIR_U, &ALL_MOVES[15]);
    cp_move(COL_4_DIR_R, &ALL_MOVES[16]);
    cp_move(COL_4_DIR_D, &ALL_MOVES[17]);
    cp_move(COL_4_DIR_L, &ALL_MOVES[18]);
    cp_move(COL_5_DIR_U, &ALL_MOVES[19]);
    cp_move(COL_5_DIR_D, &ALL_MOVES[20]);
    cp_move(COL_5_DIR_L, &ALL_MOVES[21]);
}

int move_patterns(MOVE **ret_patterns, bool no_chigiri, int heights[MAX_COL], bool for_double) {
    init_moves();
    MOVE patterns[22];
    int count = 0;
    if (heights[0] < MAX_ROW - 2) {
        patterns[count++] = COL_0_DIR_U;
        patterns[count++] = COL_0_DIR_D;
    }
    if (heights[1] < MAX_ROW - 2) {
        patterns[count++] = COL_1_DIR_U;
        if (!for_double) patterns[count++] = COL_1_DIR_D;
    }
    if (heights[2] < MAX_ROW - 2) {
        patterns[count++] = COL_2_DIR_U;
        if (!for_double) patterns[count++] = COL_2_DIR_D;
    }
    if (heights[3] < MAX_ROW - 2) {
        patterns[count++] = COL_3_DIR_U;
        if (!for_double) patterns[count++] = COL_3_DIR_D;
    }
    if (heights[4] < MAX_ROW - 2) {
        patterns[count++] = COL_4_DIR_U;
        if (!for_double) patterns[count++] = COL_4_DIR_D;
    }
    if (heights[5] < MAX_ROW - 2) {
        patterns[count++] = COL_5_DIR_U;
        if (!for_double) patterns[count++] = COL_5_DIR_D;
    }
    if (!no_chigiri || heights[0] == heights[1]) {
        patterns[count++] = COL_0_DIR_R;
        if (!for_double) patterns[count++] = COL_1_DIR_L;
    }
    if (!no_chigiri || heights[1] == heights[2]) {
        patterns[count++] = COL_1_DIR_R;
        if (!for_double) patterns[count++] = COL_2_DIR_L;
    }
    if (!no_chigiri || heights[2] == heights[3]) {
        patterns[count++] = COL_2_DIR_R;
        if (!for_double) patterns[count++] = COL_3_DIR_L;
    }
    if (!no_chigiri || heights[3] == heights[4]) {
        patterns[count++] = COL_3_DIR_R;
        if (!for_double) patterns[count++] = COL_4_DIR_L;
    }
    if (!no_chigiri || heights[4] == heights[5]) {
        patterns[count++] = COL_4_DIR_R;
        if (!for_double) patterns[count++] = COL_5_DIR_L;
    }

    (*ret_patterns) = (MOVE *)malloc(sizeof(MOVE) * count);
    memcpy((*ret_patterns), patterns, sizeof(MOVE) * count);

    return count;
}

void print_heights(int heights[]) {
    printf("[%d, %d, %d, %d, %d, %d]\n",
           heights[0],
           heights[1],
           heights[2],
           heights[3],
           heights[4],
           heights[5]);
}

void print_moves(MOVE *moves, int size) {
    for (int i = 0; i < size; i++) {
        print_move(moves[i]);
    }
    /* char directions[4] = { 'U', 'R', 'D', 'L' };  */
    /* for (int i = 0; i < size; i++) { */
    /*     printf("%d%c", moves[i].col, directions[moves[i].dir]); */
    /* } */
    /* puts(""); */
}

int next_move_patterns(MOVE_NODE **children, MOVE_NODE *parent, bool no_chigiri, bool for_double) {
    // MOVE の全パタン
    MOVE *patterns;
    int children_size = move_patterns(&patterns, no_chigiri, parent->heights, for_double);
    (*children) = (MOVE_NODE *)malloc(sizeof(MOVE_NODE) * children_size);

    //print_heights(parent->heights);
    for (int i = 0; i < children_size; i++) {
        MOVE_NODE *child = (*children) + i;
        MOVE move = patterns[i];

        //child->parent = parent;
        memcpy(child->moves, parent->moves, sizeof(MOVE) * parent->moves_size);
        child->moves[parent->moves_size] = move;
        child->moves_size = parent->moves_size + 1;
        for (int col = 0; col < MAX_COL; col++) child->heights[col] = parent->heights[col];
        child->heights[move.occupations[0]]++;
        child->heights[move.occupations[1]]++;
    }
    free(patterns);
    return children_size;
}

int all_depth_patterns(MOVE_NODE **nodes, int depth, bool no_chigiri, int initial_heights[6], char *for_pattern) {
    MOVE_NODE root = { {}, 0, { 0, 0, 0, 0, 0, 0 } };

    int current_nodes_size = 1;
    MOVE_NODE *current_nodes = (MOVE_NODE *)malloc(sizeof(MOVE_NODE) * current_nodes_size);
    size_t next_nodes_size;
    MOVE_NODE *next_nodes;

    for (int d = 0; d < depth; d++) {
        next_nodes_size = 0;
        next_nodes = (MOVE_NODE *)malloc(sizeof(MOVE_NODE) * 1);
        clock_t start = clock();
        for (int node_index = 0; node_index < current_nodes_size; node_index++) {
            MOVE_NODE *nodes_tmp;
            bool for_double = false;
            if (for_pattern) {
                for_double = for_pattern[2 * d] == for_pattern[2 * d + 1];
            }
            int count = next_move_patterns(&nodes_tmp, current_nodes + node_index, true, for_double);
            next_nodes = (MOVE_NODE *)realloc(next_nodes, sizeof(MOVE_NODE) * (next_nodes_size + count));
            memcpy(next_nodes + next_nodes_size, nodes_tmp, sizeof(MOVE_NODE) * count);
            next_nodes_size += count;
            free(nodes_tmp);
        }
        clock_t end = clock();
        printf("depth=%d, next_nodes_size=%zu (%0.2f sec)\n", d + 1, next_nodes_size, (double)(end - start) / CLOCKS_PER_SEC);
        free(current_nodes);
        current_nodes = next_nodes;
        current_nodes_size = next_nodes_size;
    }

    (*nodes) = next_nodes;

    return (int)next_nodes_size;
}
