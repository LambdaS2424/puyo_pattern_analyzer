#ifndef ___SEQUENCE_H___
#define ___SEQUENCE_H___

typedef struct _SEQUENCE {
    int id;
    char color[512];
    char pattern[512];
    char sorted_pattern[512];
} SEQUENCE;

int read_sequences_from_file(SEQUENCE **sequences, char *file_path);

void print_sequence(SEQUENCE sequence);

#endif//___SEQUENCE_H___
