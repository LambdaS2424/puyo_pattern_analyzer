#include <stdio.h>
#include <stdlib.h>

#include "puyo.h"

int main(void) {
    char field[FIELD_SIZE];
    load_field(field, "resources/tsumo_fields/field001.shp");
    print_field(field);
    int group_field[FIELD_SIZE];
    group_field_values(group_field, field);


    for (int row = MAX_ROW - 1; row >= 0; row--) {
        for (int col = 0; col < MAX_COL; col++) {
            printf("% 3d", group_field[COORD(col, row)]);
        }
        putchar('\n');
    }
    return 0;
}

int _main(void) {
    char field[FIELD_SIZE];
    init_field(field);
    print_field(field);

    SEQUENCE *sequences;
    char file_path[] = "/Users/yohei/Developer/puyo/lambda_puyo_note/resources/zenkeshi_candidates/depth_6_colors_3.csv";
    int read_count = read_sequences_from_file(&sequences, file_path);

    if (read_count < 0) {
        printf("failed to read sequences from file %s\n", file_path);
        return -1;
    }
    
    printf("read_count=%d\n", read_count);
    print_sequence(sequences[0]);

    //
    // Move
    //
    int initial_heights[] = { 0, 0, 0, 0, 0, 0 };
    int depth = 4;
    bool no_chigiri = true;
    MOVE_NODE *move_nodes;
    int move_nodes_size = all_depth_patterns(&move_nodes, depth, no_chigiri, initial_heights, sequences[0].sorted_pattern);

    /* printf("depth=%d, no_chigiri=%d, move_nodes_size=%d, move_nodes=%p\n", depth, no_chigiri, move_nodes_size, move_nodes); */
    /* printf("&move_nodes[0]=%p, &move_nodes[0].moves=%p, moves_size=%d\n", &move_nodes[0], move_nodes[0].moves, move_nodes[0].moves_size); */
    /*  */
    print_moves(move_nodes[1000].moves, depth);
    place(field, sequences[0].sorted_pattern, move_nodes[1000].moves, 0, depth - 1);
    print_field(field);

    free(move_nodes);
    free(sequences);
    return 0;
}
