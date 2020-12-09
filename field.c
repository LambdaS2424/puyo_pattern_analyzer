#include "puyo.h"

#include <stdio.h>
#include <string.h>

char *init_field(char *field) {
    strcpy(field, INITIAL_FIELD);
    return field;
}

char *load_field(char *field, char *file_path) {
    FILE *fp;
    fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("failed to open file %s\n", file_path);
        return NULL;
    }

    char line[64];

    for (int row = MAX_ROW - 1; row >= 0; row--) {
        if (fgets(line, 64, fp) == NULL) break;
        strncpy(&field[COORD(0, row)], line, MAX_COL);
    }

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

#define INIT_ARRAY(arr, value, length) { for (int i = 0; i < length; i++) arr[i] = value; }

#define SAME_VALUE(col, row, index, field, group_field) (VALID_COL(col) && VALID_ROW(row) && group_field[COORD(col, row)] != group_field[index] && field[COORD(col, row)] == field[index])

void group_field_values(int group_field[FIELD_SIZE], char field[FIELD_SIZE]) {
    int remains = 0;
    int buf1[FIELD_SIZE] = { -1 };
    int buf2[FIELD_SIZE] = { -1 };
    int *current;
    int *next;
    int next_count = 0;

    INIT_ARRAY(group_field, -1, FIELD_SIZE);

    group_field[0] = 1;
    for (int i = 1; i < FIELD_SIZE; i++) {
        group_field[i] = (field[i] == '_' ? 0 : -(i + 1));
    }

    buf1[0] = 0;
    current = buf1;
    next = buf2;
    while (true) {
        for (int i = 0; current[i] != -1; i++) {
            int ref_index = current[i];
            int col = COL(ref_index);
            int row = ROW(ref_index);

            if (SAME_VALUE(col, row + 1, ref_index, field, group_field)) {
                int added_index = COORD(col, row + 1);
                group_field[added_index] = group_field[ref_index];
                next[next_count++] = added_index;
            }

            if (SAME_VALUE(col + 1, row, ref_index, field, group_field)) {
                int added_index = COORD(col + 1, row);
                group_field[added_index] = group_field[ref_index];
                next[next_count++] = added_index;
            }

            if (SAME_VALUE(col, row - 1, ref_index, field, group_field)) {
                int added_index = COORD(col, row - 1);
                group_field[added_index] = group_field[ref_index];
                next[next_count++] = added_index;
            }

            if (SAME_VALUE(col - 1, row, ref_index, field, group_field)) {
                int added_index = COORD(col - 1, row);
                group_field[added_index] = group_field[ref_index];
                next[next_count++] = added_index;
            }
        }

        if (next_count == 0) {
            int i = 0;
            for (; i < FIELD_SIZE; i++) {
                if (group_field[i] < 0) {
                    group_field[i] *= -1;
                    next[next_count++] = i;
                    break;
                }
            }
            if (i == FIELD_SIZE) break;
        }

        int *tmp = current;
        current = next;
        next = tmp;

        INIT_ARRAY(next, -1, FIELD_SIZE);
        next_count = 0;
    }
}
