#ifndef ___FIELD_H___
#define ___FIELD_H___

#define MAX_COL (6)
#define MAX_ROW (14)
#define FIELD_SIZE (MAX_COL * MAX_ROW + 1)

#define INITIAL_FIELD ("____________________________________________________________________________________")

#define COORD(col, row) ((MAX_COL * (row)) + (col))
#define ROW(index) ((index) / MAX_ROW)
#define COL(index) ((index) % MAX_COL)

char *init_field(char *field);

void print_field(char *field);

char *place(char *field, char *tsumo_parttern, MOVE *moves, int depth_from, int depth_to);

int height(char *field, int col);

void group_field_values(char *field);

#endif//___FIELD_H___
