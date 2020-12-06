#include "puyo.h"

#include <stdio.h>
#include <stdlib.h>

int read_sequences_from_file(SEQUENCE **sequences, char *file_path) {
    FILE *fp;
    fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("failed to open file %s\n", file_path);
        return -1;
    }

    SEQUENCE *seqs = (SEQUENCE *)malloc(sizeof(SEQUENCE) * 65536);
    int read_count = 0;

    while (fscanf(fp,
                 "%d,%[^,],%[^,],%s",
                 &seqs[read_count].id,
                 seqs[read_count].color,
                 seqs[read_count].pattern,
                 seqs[read_count].sorted_pattern) != EOF) {
        read_count++;
    }

    fclose(fp);

    (*sequences) = (SEQUENCE *)realloc(seqs, sizeof(SEQUENCE) * read_count);

    return read_count;
}

void print_sequence(SEQUENCE sequence) {
    printf("id=%d\ncolor=%s\npattern=%s\nsorted_pattern=%s\n",
           sequence.id,
           sequence.color,
           sequence.pattern,
           sequence.sorted_pattern);
}
