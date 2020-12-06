#include "puyo.h"

#include <stdio.h>
#include <string.h>

char *init_field(char *field) {
    strcpy(field, INITIAL_FIELD);
    return field;
}

void print_field(char *field) {
    for (int row = MAX_ROW - 1; row >= 0; row--) {
        for (int col = 0; col < MAX_COL; col++) {
            putchar(field[COORD(col, row)]);
        }
        putchar('\n');
    }
}

char *place(char *field, char *tsumo_pattern, MOVE *moves, int depth_from, int depth_to) {
    char tmp_field[MAX_COL * (MAX_ROW + 2)];
    memcpy(tmp_field, field, MAX_COL * MAX_ROW);

    for (int depth = depth_from; depth <= depth_to; depth++) {
        MOVE move = moves[depth];
        char *tsumo = tsumo_pattern + 2 * depth;

        int index1 = move.dir != DOWN;
        int index2 = move.dir == DOWN;

        int col1 = move.occupations[index1], row1 = height(tmp_field, move.occupations[index1]);
        tmp_field[COORD(col1, row1)] = tsumo[index1];
        
        int col2 = move.occupations[index2], row2 = height(tmp_field, move.occupations[index2]);
        tmp_field[COORD(col2, row2)] = tsumo[index2];
    }

    for (int col = 0; col < MAX_COL; col++) {
        if (height(tmp_field, col) > MAX_COL) return field;
    }

    memcpy(field, tmp_field, MAX_COL * MAX_ROW);

    return field;
}

int height(char *field, int col) {
    for (int row = MAX_ROW - 1; row >= 0; row--) {
        if (field[COORD(col, row)] != '_') return row + 1;
    }

    return 0;
}
